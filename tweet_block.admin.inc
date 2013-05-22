<?php

/**
 * tweet_block_settings_form
 * Administration form.
 *
 * @return Form for administering module.
 */
function tweet_block_settings_form() {
  $form = array();

  $form['tweet_block_1'] = array(
    '#type' => 'fieldset',
    '#title' => t('Tweet Block 1 - Single line display (Custom)'),
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
    '#title' => t('Tweet Block 2 - RIGHT RAIL (Twitter Embed formatting)'),
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
    '#title' => t('Tweet Block 3 - CENTER REGION (Custom)'),
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
    '#title' => t('Tweet Block 4 - RIGHT RAIL (Custom Feed)'),
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
    '#description' => t('The username of the twitter account for this block to display. (Ex: @MLS_Insider)'),
    '#default_value' => '',
    '#required' => FALSE,
  );
  
  $form['tweet_block_4']['tweet_block_4_rm'] = array(
    '#type' => 'textfield',
    '#title' => t('Read More URL - Block 4'),
    '#description' => t('The URL to link to an external read more tweets page. (Include http://)'),
    '#default_value' => '',
    '#required' => FALSE,
  );
  
  $form['submit'] = array(
   '#type' => 'submit',
   '#value' => t('Save settings'),
  );
  
  $form['feed_blocks'] = array(
    '#type' => 'fieldset',
    '#title' => t('Feed Blocks List'),
  );

  $feed_blocks = tweet_block_get_feeds();
  if ($feed_blocks) {
    foreach ($feed_blocks as $key => $feed_block) {
      $form['feed_blocks']['feed_block_' . $key] = array(
        '#prefix' => '<div>',
        '#value' => '<a href="tweetblock/edit/' . $feed_block['tweet_feed_block_id'] . '">' . t($feed_block['tweet_feed_title'] . ' - ' . $feed_block['tweet_feed_twitter_id']) . '</a> / <a href="tweetblock/remove/' . $feed_block['tweet_feed_block_id'] . '">Remove</a>',
        '#suffix' => '</div>',
      );
    }
  }
  
  return $form;
}

/**
 * tweet_block_settings_form_validate
 *  Validation for tweet_block_settings_form
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
  if (($form_state['values']['tweet_block_4_id'] != '') && ($form_state['values']['tweet_block_4_rm'] == '')) {
    form_set_error('tweet_block_4_rm', t('You must enter a value for the twitter read more link.'));
  }
}

/**
 * tweet_block_settings_form_validate
 * Validation for tweet_block_settings_form
 */
function tweet_block_settings_form_submit(&$form, &$form_state) {
  // store the ids in variables, mainly so we can revoer the values and place them in the form for defaults
  variable_set('tweet_id_1', $form_state['values']['tweet_block_1_id']);
  variable_set('tweet_id_2', $form_state['values']['tweet_block_2_id']);
  variable_set('tweet_id_3', $form_state['values']['tweet_block_3_id']);
  $i = 1;
  $blocks_built = 0;
  // cycle through the 3 blocks, tbd make this extensible to have more than 3
  while ($i<4) {
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
  
  if($form_state['values']['tweet_block_4_id']) {
    tweet_block_set_feed_info($form_state['values']['tweet_block_4_title'], $form_state['values']['tweet_block_4_id'], $form_state['values']['tweet_block_4_rm']);
  }
}