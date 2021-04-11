import os
import requests
import urllib.parse

from flask import Flask, flash, redirect, render_template, request, session
from functools import wraps


def apology(message, code=400):
    """Render message as an apology to user."""
    def escape(s):
        """
        Escape special characters.

        https://github.com/jacebrowning/memegen#special-characters
        """
        for old, new in [("-", "--"), (" ", "-"), ("_", "__"), ("?", "~q"),
                         ("%", "~p"), ("#", "~h"), ("/", "~s"), ("\"", "''")]:
            s = s.replace(old, new)
        return s
    return render_template("apology.html", top=code, bottom=escape(message)), code


def login_required(f):
    """
    Decorate routes to require login.

    https://flask.palletsprojects.com/en/1.1.x/patterns/viewdecorators/
    """
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get("user_id") is None:
            return redirect("/login")
        return f(*args, **kwargs)
    return decorated_function


def lookup(symbol):
    """Look up quote for symbol."""

    # Contact API
    try:
        api_key = os.environ.get("API_KEY")
        url = f"https://cloud.iexapis.com/stable/stock/{urllib.parse.quote_plus(symbol)}/quote?token={api_key}"
        response = requests.get(url)
        response.raise_for_status()
    except requests.RequestException:
        return None

    # Parse response
    try:
        quote = response.json()
        return {
            "name": quote["companyName"],
            "price": float(quote["latestPrice"]),
            "symbol": quote["symbol"]
        }
    except (KeyError, TypeError, ValueError):
        return None


def usd(value):
    """Format value as USD."""
    return f"${value:,.2f}"

"""Function to check a valid username"""
def valid_word(word):
    invalid_caracters = ";, *{}[]"
    for x in invalid_caracters:
        if x in word:
            return -1
        else:
            return 0

def valid_password(password):
    invalid_caracters = ";, *{}[]"
    if not password:
        return -1
    for y in invalid_caracters:
        if y in password:
            return -1
        else:
            return 0

def valid_quantity(number_string):
    valid_number = "1234567890"
    for x in number_string:
        if x not in valid_number:
            return -1
    return 0

def valid_symbol(symbol):
    invalid_caracters = ";, *{}[]"
    count = 0
    if symbol is None:
        return -1
    for x in invalid_caracters:
        count = count + 1
        if x in symbol:
            return -1
        else:
            return 0
    if count == 0:
        return -1
