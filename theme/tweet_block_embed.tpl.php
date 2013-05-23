<?php if (!empty($tweet_content['tweet_markup'])): ?>
  <div class="tweet-block embedd">
    <?php
      print $tweet_content['tweet_markup'];
    ?>
  </div>
<?php endif; ?>
