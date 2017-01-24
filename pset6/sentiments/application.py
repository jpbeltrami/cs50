from flask import Flask, redirect, render_template, request, url_for

import helpers
import os
import sys
from analyzer import Analyzer

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/search")
def search():

    # validate screen_name
    screen_name = request.args.get("screen_name", "").lstrip("@")
    if not screen_name:
        return redirect(url_for("index"))

    # get screen_name's tweets
    tweets = helpers.get_user_timeline(screen_name, count=100)

    positives = os.path.join(sys.path[0], "positive-words.txt")
    negatives = os.path.join(sys.path[0], "negative-words.txt")
    analyzer = Analyzer(positives, negatives)
    
    total_tweets = len(tweets)
    
    positive = 0.0
    negative = 0.0
    neutral = total_tweets
    
    for tweet in tweets:
        score = analyzer.analyze(tweet)
        if score > 0:
            positive += 1
            neutral -= 1
        elif score < 0:
            negative += 1
            neutral -= 1
            
    # make positive, negative, and neutral into percentages
    
    positive = (positive / total_tweets) * 100
    negative = (negative / total_tweets) * 100
    neutral = (neutral / total_tweets) * 100

    # generate chart
    chart = helpers.chart(positive, negative, neutral)

    # render results
    return render_template("search.html", chart=chart, screen_name=screen_name)
