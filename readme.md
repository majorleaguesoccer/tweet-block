# tweet_block

Twitter launched some new tools that allows users to embedd tweets and timelines. You can grab the code from a specific tweet from the tweet's detail page OR you can use the Twitter's oEmbed endpoint (https://dev.twitter.com/docs/embedded-tweets, https://dev.twitter.com/docs/embedded-timelines). This module uses the oEmbed endpoint call to generate static pre-formatted blocks to your site to be used via blocks where ever you like. It also allows for an unlimited amount of embedded timelines to be created.

The oEmbed api can go and request the information about the tweet and generate the embedded block.
NOTE: This is not a live updating block of tweets, this leverages the twitter oEmbed using the tweetid you specified in the admin settings. The block is static unless you update the ID in the settings.

There is a limit to # of API request you can do per hour (150). This module stashes the response in the db and only makes requests when you save the settings form.

Content is not written into the block unless an ID is specified and the twitter response is valid.

This module generates the following blocks

* Block 1 - The proper response from the twitter API formatter by twitter. The twitter JS is required and is an option in the admin for this block.
* Block 2 - A custom single line representation of the tweet. You can override the styles and theme yourself.
* Block 3 - A stylized version of the tweet that you can skin yourself.
* Block 4[n] - Unlimited amount of embedded timelines.

We are very open to making modifications to this module and it is in active development, please let us know what you would like to see in the issue cue.

