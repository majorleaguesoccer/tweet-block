<?php if (!empty($tweet_content['tweet_markup'])): ?>
  <div class="tweet-block center clearfix">
    <div class="tweet">
      <span class="bqstart">&#8220;</span>
    <?php
      // Strip the tweet
      $pattern = "/<p>(.*?)<\/p>/";
      preg_match($pattern, $tweet_content['tweet_markup'], $tweet);
      print '<p>' . $tweet[1] . '</p>';
    ?>
    </div>
    <div class="author">~ <?php print $tweet_content['tweet_author_name'] ?></div><a href="<?php print $tweet_content['tweet_author_url'] ?>" class="twitter-follow-button" data-show-count="false">Follow <?php print $tweet_content['tweet_author_name'] ?></a>
    <div class="intents">
      <ul>
        <li><a href="https://twitter.com/intent/tweet?in_reply_to=<?php print $tweet_content['tweet_id']; ?>" class="reply-action twt-intent" title="Reply"><i></i><b>Reply</b></a></li>
        <li class="rt"><a href="https://twitter.com/intent/retweet?tweet_id=<?php print $tweet_content['tweet_id']; ?>" class=" retweet-action  twt-intent" title="Retweet"><i></i><b>Retweet</b></a></li>
        <li class="fav"><a href="https://twitter.com/intent/favorite?tweet_id=<?php print $tweet_content['tweet_id']; ?>" class=" favorite-action  twt-intent" title="Favorite"><i></i><b>Favorite</b></a></li>
      </ul>
    </div>
  </div>
<?php endif; ?>
