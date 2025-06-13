import praw

CID = 'd9q1g4dDXYf8O59Jdz-r1w'
CSK = 'LqnAdyzYvxozWOaUYig4-cHIRAPAyg'
UA = 'script:firstPraw:v1.0 (by /u/SplashmanDoon)'

reddit = praw.Reddit(
    client_id = CID,
    client_secret = CSK,
    user_agent = UA,
)

invSubReddit = reddit.subreddit('investing')

for submission in invSubReddit.hot(limit=5):
    print(submission.title)