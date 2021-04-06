import os, datetime

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, valid_word, valid_password, valid_quantity

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")

@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    actual_users = db.execute("SELECT username, cash FROM users WHERE id = ?", session["user_id"])
    print(actual_users)
    actual_cash = actual_users[0]["cash"]

    #actual_session = session["user_id"]
    rows = db.execute("SELECT share, name, no_share FROM resume WHERE user_id = ?", session["user_id"])

    #Request actual price of each user share
    for row in rows:
        actual_price = lookup(row["share"])

        #Check if share symbol is valid
        if actual_price is None:
            return apology("Share symbol is incorrect, please text a valid symbol")

        no_shares = row["no_share"]
        total = actual_price["price"] * no_shares
        actual_cash = actual_cash + total
        db.execute("UPDATE resume SET price = ?, total = ? WHERE share = ? AND user_id = ?", actual_price["price"], total, actual_price["symbol"], session["user_id"])

    rows = db.execute("SELECT id, share, name, no_share, price, total FROM resume WHERE user_id = ? AND no_share > 0", session["user_id"])

    return render_template("index.html", actual_users=actual_users, rows=rows, actual_cash=actual_cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    else:
        symbol_buy = request.form.get("symbol")
        quantity_buy_aux = request.form.get("shares")

        if valid_quantity(quantity_buy_aux) != 0:
            return apology("Shares quantity is an invalid number")


        #Check if quantity field is not empty
        if len(quantity_buy_aux) == 0:
            return apology("Quantity field is empty, please text a value")

        quantity_buy = int(quantity_buy_aux)

        #Check is quantity field is not a negative number nor zero
        if quantity_buy <= 0:
            return apology("Invalid share quantity, please text a valid number")

        share_buy = lookup(symbol_buy)

        #Verify valid quantity for buying
        if quantity_buy <= 0:
            return apology("Invalid quantity")

        #Check if share symbol is valid
        if share_buy is None:
            return apology("Share symbol is incorrect, please text a valid symbol")

        #Calculate total cash for buying
        total_buy = quantity_buy * share_buy["price"]
        # Actual date
        actual_date = datetime.datetime.now()

        rows = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])

        #Check if you have enough cash for buying
        if total_buy > rows[0]["cash"]:
            return apology("You don't have enough cash for buying these shares")
        else:
            new_total = rows[0]["cash"] - total_buy
            db.execute("UPDATE users SET cash = ? WHERE id = ?", new_total, session["user_id"])
            db.execute("INSERT INTO transactions (user_id, action, date, share, no_shares, value) VALUES (?, ?, ?, ?, ?, ?)", session["user_id"], "Buy", actual_date, share_buy["symbol"], quantity_buy, total_buy )

            rows = db.execute("SELECT share, no_share FROM resume WHERE share = ? AND user_id = ?", share_buy["symbol"], session["user_id"])

            if len(rows) == 0:
                db.execute("INSERT INTO resume (user_id, share, name, no_share) VALUES (?, ?, ?, ?)", session["user_id"], share_buy["symbol"], share_buy["name"], quantity_buy)
            else:
                new_shares = rows[0]["no_share"] + quantity_buy
                db.execute("UPDATE resume SET no_share = ? WHERE share = ? AND user_id = ?", new_shares, share_buy["symbol"], session["user_id"])

    return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    historic = db.execute("SELECT id, action, date, share, no_shares, value FROM transactions WHERE user_id = ?", session["user_id"])
    return render_template("history.html", historic=historic)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]
        print("ID number is {}".format(session["user_id"]))

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")
    else:
        symbol = request.form.get("symbol")
        actual_share = lookup(symbol)

        #Check if share symbol is valid
        if actual_share is None:
            return apology("Share symbol is incorrect, please text a valid symbol")

    return render_template("quote_result.html", name=actual_share["name"], symbol=actual_share["symbol"], price=actual_share["price"])


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "GET":
        return render_template("register.html")
    else:
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        check_word = valid_word(username)
        if check_word != 0:
            return apology("Invalid username, please text a valid username")
        check_password = valid_password(password)
        if check_password != 0:
            return apology("Invalid password, please text a valid password")

        actual_users = db.execute("SELECT username FROM users")
        for x in actual_users:
            if x["username"] == username:
                return apology("User is actually used, choose another one", 400)

        if password != confirmation:
            return apology("Passwords are not equals", 400)

        if not(username and username.strip()):
            return apology("Type a username", 400)

        if not(password and password.strip()):
            return apology("Type a password", 400)

        #encrypted password by a hash function
        password_hash = generate_password_hash(password)

        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, password_hash)

        return redirect("/")

    """Register user"""
    """return apology("TODO")"""


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        share_list = db.execute("SELECT share FROM resume WHERE user_id = ? AND no_share > 0", session["user_id"])
        return render_template("sell.html", share_list=share_list)
    else:
        # Actual date
        actual_date = datetime.datetime.now()
        # Get values from form request
        symbol_sell = request.form.get("symbol_sell")
        quantity_sell_aux = request.form.get("quantity")
        #Check if quantity is a valid number
        if valid_quantity(quantity_sell_aux) != 0:
            return apology("Shares quantity is an invalid number")

        if len(quantity_sell_aux) == 0:
            return apology("Quantity field is empty, please text a value")

        quantity_sell = int(quantity_sell_aux)

        if quantity_sell <= 0:
            return apology("Invalid share quantity, please text a valid number")

        # Check data of actual share
        actual_share = lookup(symbol_sell)

        #Verify valid quantity for buying
        if quantity_sell <= 0:
            return apology("Invalid quantity")

        #Check if share symbol is valid
        if actual_share is None:
            return apology("Share symbol is incorrect, please text a valid symbol")

        rows = db.execute("SELECT no_share FROM resume WHERE user_id = ? AND share = ?", session["user_id"], symbol_sell)

        #Check if you have enough shares for selling
        if rows[0]["no_share"] >= quantity_sell:
            #Calculate total sell and update transactions table
            shares_updated = rows[0]["no_share"] - quantity_sell
            total_sell = quantity_sell * actual_share["price"]
            quantity_sell = quantity_sell * -1
            db.execute("INSERT INTO transactions (user_id, action, date, share, no_shares, value) VALUES (?, ?, ?, ?, ?, ?)", session["user_id"], "Sell", actual_date, symbol_sell, quantity_sell, total_sell)

            #Request the actual cash for actual user
            actual_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
            cash_updated = actual_cash[0]["cash"] + total_sell
            db.execute("UPDATE users SET cash = ? WHERE id = ?", cash_updated, session["user_id"])

            #Update resume table
            db.execute("UPDATE resume SET no_share = ? WHERE user_id = ? AND share = ?", shares_updated, session["user_id"], symbol_sell)
            return redirect("/")

        else:
            return apology("You don't have enough shares for selling, sorry")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
