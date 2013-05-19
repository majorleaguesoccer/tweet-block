<?php if (!empty($tweet_content['tweet_markup'])): ?>
  <div class="tweet-block right">
    <?php
      print $tweet_content['tweet_markup'];
    ?>
  </div>
<?php endif; ?>
