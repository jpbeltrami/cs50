import os
import nltk

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""
        self.positives = set()
        self.negatives = set()
        
        file = open(positives, 'r')
        for line in file:
            if line.startswith(';'):
                continue
            else:
                self.positives.add(line.strip())
                
        file = open(negatives, 'r')
        for line in file:
            if line.startswith(';'):
                continue
            else:
                self.negatives.add(line.strip())
            

    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""
            
        # Calculate text's total score
        score = 0
        tokenizer = nltk.tokenize.TweetTokenizer()
        tokens = tokenizer.tokenize(text)
        # iterate over tokens
        for word in tokens:
            # check to see if this token is positive or negative
            if word.lower() in self.positives:
                score += 1
            elif word.lower() in self.negatives: 
                score -= 1
            else:
                continue
        
        return score

