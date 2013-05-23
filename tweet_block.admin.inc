<?php
/**
 * @file
 * Tweet block admin forms
 */

/**
 * Tweet block settings form.
 */
function tweet_block_settings_form() {

  $form = array();

  $form['tweet_block_script'] = array(
    '#title' => t('Include twitter javascript.'),
    '#type' => 'checkbox',
    '#description' => t('Some blocks used by this module (Block 1 and Timelines) require the twitter widget.js to render. If you are already including this script, you can uncheck this box.'),
    '#default_value' => variable_get('tweet_block_script', TRUE),
    '#required' => FALSE,
  );

  $form['tweet_block_1'] = array(
    '#type' => 'fieldset',
    '#title' => t('Tweet Block #1 - Custom thin'),
    '#description' => t('A single line display block of the specified tweet.'),
  );

  $form['tweet_block_1']['tweet_block_1_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Tweet Block ID - Block 1'),
    '#description' => t('The ID of the tweet for this block, excluding an ID will not generate a block for this tweet block'),
    '#default_value' => variable_get('tweet_id_1', FALSE),
    '#required' => FALSE,
  );

  $form['tweet_block_2'] = array(
    '#type' => 'fieldset',
    '#title' => t('Tweet Block #2 - Twitter Embed formatting'),
    '#description' => t('A twitter formatter display block of the specified tweet for the RIGHT RAIL (300px)'),
  );

  $form['tweet_block_2']['tweet_block_2_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Tweet Block ID - Block 2'),
    '#description' => t('The ID of the tweet for this block, excluding an ID will not generate a block for this tweet block'),
    '#default_value' => variable_get('tweet_id_2', FALSE),
    '#required' => FALSE,
  );

  $form['tweet_block_3'] = array(
    '#type' => 'fieldset',
    '#title' => t('Tweet Block #3 - Custom tall'),
    '#description' => t('A twitter formatter display block of the specified tweet for the CENTER REGION (620px)'),
  );

  $form['tweet_block_3']['tweet_block_3_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Tweet Block ID - Block 3'),
    '#description' => t('The ID of the tweet for this block, excluding an ID will not generate a block for this tweet block'),
    '#default_value' => variable_get('tweet_id_3', FALSE),
    '#required' => FALSE,
  );
  
  $form['tweet_block_4'] = array(
    '#type' => 'fieldset',
    '#title' => t('Tweet Block - Embedded Timeline'),
    '#description' => t('A twitter formatter display block of the specified feed for the RIGHT RAIL (300px)'),
  );
  
  $form['tweet_block_4']['tweet_block_4_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Block Title - Block 4'),
    '#description' => t('Block title to display.'),
    '#default_value' => '',
    '#required' => FALSE,
  );

  $form['tweet_block_4']['tweet_block_4_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Twitter Username - Block 4'),
    '#description' => t('The username of the twitter account for this block to display. (Ex: @hansyg)'),
    '#default_value' => '',
    '#required' => FALSE,
  );
  
  $form['tweet_block_4']['tweet_block_4_widget_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Widget ID - Block 4'),
    '#description' => t('The widget ID of your timeline. Go to the widgets section of your twitter page. https://twitter.com/settings/widgets to get the ID of the timeline you are creating.'),
    '#default_value' => '',
    '#required' => FALSE,
  );
  
  $form['submit'] = array(
   '#type' => 'submit',
   '#value' => t('Save settings'),
  );
  
  $form['tweet_block_feed_blocks'] = array(
    '#type' => 'fieldset',
    '#title' => t('Feed Blocks List'),
  );

  $feed_blocks = tweet_block_get_feeds();

  if ($feed_blocks) {
    foreach ($feed_blocks as $key => $feed_block) {
      $form['tweet_block_feed_blocks']['feed_block_' . $key] = array(
        '#prefix' => '<div>',
        '#value' => '<a href="tweetblock/edit/' . $feed_block['tweet_feed_block_id'] . '">' . t($feed_block['tweet_feed_title'] . '</a> - Twitter User: ' . $feed_block['tweet_feed_twitter_id']) . '</a> --- <a href="tweetblock/edit/' . $feed_block['tweet_feed_block_id'] . '">Edit</a> | <a href="tweetblock/remove/' . $feed_block['tweet_feed_block_id'] . '">Remove</a>',
        '#suffix' => '</div>',
      );
    }
  }
  
  return $form;
}

/**
 * Validation for tweet_block_settings_form.
 */
function tweet_block_settings_form_validate(&$form, &$form_state) {
  if (($form_state['values']['tweet_block_1_id'] != '') && !is_numeric($form_state['values']['tweet_block_1_id'])) {
    form_set_error('tweet_block_1_id', t('You must enter a number for the tweet id.'));
  }
  if (($form_state['values']['tweet_block_2_id'] != '') && !is_numeric($form_state['values']['tweet_block_2_id'])) {
    form_set_error('tweet_block_2_id', t('You must enter a number for the tweet id.'));
  }
  if (($form_state['values']['tweet_block_3_id'] != '') && !is_numeric($form_state['values']['tweet_block_3_id'])) {
    form_set_error('tweet_block_3_id', t('You must enter a number for the tweet id.'));
  }
  if (($form_state['values']['tweet_block_4_id'] != '') && ($form_state['values']['tweet_block_4_widget_id'] == '')) {
    form_set_error('tweet_block_4_widget_id', t('You must enter a value for the widget id for the timeline to work. See https://dev.twitter.com/docs/embedded-timelines.'));
  }
}

/**
 * Submission handler for tweet_block_settings_form.
 */
function tweet_block_settings_form_submit(&$form, &$form_state) {
  // store the ids in variables, mainly so we can recover the values and place them in the form for defaults.
  variable_set('tweet_id_1', $form_state['values']['tweet_block_1_id']);
  variable_set('tweet_id_2', $form_state['values']['tweet_block_2_id']);
  variable_set('tweet_id_3', $form_state['values']['tweet_block_3_id']);
  variable_set('tweet_block_script', $form_state['values']['tweet_block_script']);
  
  $i = 1;
  $blocks_built = 0;
  if ($form_state['values']['tweet_block_4_id']) {
    tweet_block_set_feed_info($form_state['values']['tweet_block_4_title'], $form_state['values']['tweet_block_4_id'], $form_state['values']['tweet_block_4_rm']);
    $blocks_built++;
  }
  // cycle through the 3 custom blocks, TBD make this extensible to have more than 3
  while ($i < 4) {
    $form_value_id = 'tweet_block_' . $i . '_id';
    if ($form_state['values'][$form_value_id] != "") {
      // ping the twitter api if ID exists
      $block_content = tweet_block_get_tweet($form_state['values'][$form_value_id]);
      // stash ID and html JSON response in the db
      tweet_block_set_tweet_info($i, $form_state['values'][$form_value_id], $block_content);
      $blocks_built++;
    }
    else {
      tweet_block_delete_tweet_info($i);
    }
    $i++;
  }
  drupal_set_message(t('Your tweet block settings have been saved. ' . $blocks_built . ' blocks have been generated and are available through the block system.'));

}

/**
 * Tweet block - Edit feed block settings form.
 */
function tweet_block_edit_form() {
  $form = array();
  $id = arg(4);
  $feed_block = tweet_block_get_feed($id);
  $form['tweet_block_edit'] = array(
    '#type' => 'fieldset',
    '#title' => t('Feed Block ' . $id . ' - RIGHT RAIL (Custom Feed)'),
    '#description' => t('A twitter formatter display block of the specified feed for the RIGHT RAIL (300px)'),
  );
  
  $form['tweet_block_edit']['tweet_block_4_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Block Title'),
    '#description' => t('Block title to display.'),
    '#default_value' => $feed_block['tweet_feed_title'],
    '#value' => $feed_block['tweet_feed_title'],
    '#required' => FALSE,
  );

  $form['tweet_block_edit']['tweet_block_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Twitter Username'),
    '#description' => t('The username of the twitter account for this block to display. (Ex: @MLS_Insider)'),
    '#default_value' => $feed_block['tweet_feed_twitter_id'],
    '#value' => $feed_block['tweet_feed_twitter_id'],
    '#required' => FALSE,
  );
  
  $form['tweet_block_edit']['tweet_block_rm'] = array(
    '#type' => 'textfield',
    '#title' => t('Read More URL'),
    '#description' => t('The URL to link to an external read more tweets page. (Include http://)'),
    '#default_value' => $feed_block['tweet_feed_read_more_url'],
    '#value' => $feed_block['tweet_feed_read_more_url'],
    '#required' => FALSE,
  );
  
  $form['submit'] = array(
   '#type' => 'submit',
   '#value' => t('Save settings'),
  );
  
  $form['cancel'] = array(
   '#value' => '<a href="/admin/settings/tweetblock">' . t('Cancel') . '</a>',
  );
  
  return $form;
}
