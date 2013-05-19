<script charset="utf-8" src="//widgets.twimg.com/j/2/widget.js"></script>
<?php
  $widget = "<script>
  new TWTR.Widget({
    version: 2,
    type: 'profile',
    rpp: 3,
    interval: 30000,
    width: 280,
    height: 264,
    theme: {
      shell: {
        background: '#FFF',
        color: '#000'
      },
      tweets: {
        background: '#FFF',
        color: '#000',
        links: '#2864b4'
      }
    },
    features: {
      scrollbar: false,
      loop: false,
      live: true,
      timestamp: true,
      avatars: true,
      behavior: 'all',
      toptweets: false
    }
  }).render().setUser('" . $content['username'] . "').start();
  </script>";
  print $widget;
?>
<div class="twitter-footer"><p><a href="<?php print $content['read_more']; ?>">Read more tweets</a> &nbsp;|&nbsp; <a href="http://twitter.com/<?php print $content['username']; ?>">Follow us on Twitter</a><img align="right" class="arrow" src="/sites/all/modules/custom/tweet_block/theme/images/right_rail_element_footer_more-arrow.gif"></p></div>