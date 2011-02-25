<?php

/**
 * Settings page
 */
function commentsection_settings() {
  $form['commentsection_base'] = array(
    '#type' => 'textfield',
    '#title' => t('Base URL'),
    '#default_value' => variable_get('commentsection_base', ''),
  );
   $form['commentsection_source'] = array(
    '#type' => 'textfield',
    '#title' => t('XML URL'),
    '#default_value' => variable_get('commentsection_source', ''),
  );
  $form['commentsection_xpath_indicator'] = array(
    '#type' => 'textfield',
    '#title' => t('XPath to publish indicator'),
    '#default_value' => variable_get('commentsection_xpath_indicator', ''),
    '#description' => t('You may provide multiple XPaths expressions seperated by the | operator. The first result will be used. For further XPath instructions have a look at !url', array('!url' => l('w3schools.com', 'http://www.w3schools.com/xpath/xpath_syntax.asp'))),
  );
  $form['commentsection_xpath_title'] = array(
    '#type' => 'textfield',
    '#title' => t('XPath to title'),
    '#default_value' => variable_get('commentsection_xpath_title', '//title'),
    '#description' => t('You may provide multiple XPaths expressions seperated by the | operator. The first result will be used. For further XPath instructions have a look at !url', array('!url' => l('w3schools.com', 'http://www.w3schools.com/xpath/xpath_syntax.asp'))),
  );
  $form['commentsection_xpath_body'] = array(
    '#type' => 'textfield',
    '#title' => t('XPath to body'),
    '#default_value' => variable_get('commentsection_xpath_body', '//body'),
    '#description' => t('You may provide multiple XPaths expressions seperated by the | operator. The first result will be used. For further XPath instructions have a look at !url', array('!url' => l('w3schools.com', 'http://www.w3schools.com/xpath/xpath_syntax.asp'))),
  );
  $form['commentsection_xpath_date'] = array(
    '#type' => 'textfield',
    '#title' => t('XPath to date'),
    '#default_value' => variable_get('commentsection_xpath_date', '//date'),
    '#description' => t('You may provide multiple XPaths expressions seperated by the | operator. The first result will be used. For further XPath instructions have a look at !url', array('!url' => l('w3schools.com', 'http://www.w3schools.com/xpath/xpath_syntax.asp'))),
  );
  $form['commentsection_xpath_author'] = array(
    '#type' => 'textfield',
    '#title' => t('XPath to author'),
    '#default_value' => variable_get('commentsection_xpath_author', '//author'),
    '#description' => t('You may provide multiple XPaths expressions seperated by the | operator. The first result will be used. For further XPath instructions have a look at !url', array('!url' => l('w3schools.com', 'http://www.w3schools.com/xpath/xpath_syntax.asp'))),
  );
  $form['commentsection_original_author'] = array(
    '#type' => 'radios',
    '#title' => t('Original author'),
    '#default_value' => variable_get('commentsection_original_author', 1),
    '#options' => array(0 => 'deactivated', 1 => 'activated'),
    '#description' => t("Use the original author as user if availlable. As fallback you should define a %default_author below.", array('%default_author' => t('Default author'))),
  );
  $form['commentsection_default_author'] = array(
    '#type' => 'textfield',
    '#title' => t('Default author'),
    '#default_value' => variable_get('commentsection_default_author', ''),
    '#autocomplete_path' => 'user/autocomplete',
    '#description' => t('Provide a default author, who will be the author of automatically published nodes. If not provided the author will be %anonymous', array('%anonymous' => variable_get('anonymous', t('anonymous')))),
  );
  $form['commentsection_xpath_taxonomy'] = array(
    '#type' => 'textfield',
    '#title' => t('XPath to taxonomy terms'),
    '#default_value' => variable_get('commentsection_xpath_taxonomy', '//keyword'),
    '#description' => t('You may provide multiple XPaths expressions seperated by the | operator. The first results will be used. For further XPath instructions have a look at !url', array('!url' => l('w3schools.com', 'http://www.w3schools.com/xpath/xpath_syntax.asp'))),
  );
  $form['commentsection_xpath_byline'] = array(
    '#type' => 'textfield',
    '#title' => t('XPath to Byline'),
    '#default_value' => variable_get('commentsection_xpath_byline', '//byline'),
    '#description' => t('You may provide multiple XPaths expressions seperated by the | operator. The first results will be used. For further XPath instructions have a look at !url', array('!url' => l('w3schools.com', 'http://www.w3schools.com/xpath/xpath_syntax.asp'))),
  );
  $vocs[] = '<'. t('none') .'>';
  foreach (taxonomy_get_vocabularies('commentsection') as $vid => $voc) {
    $vocs[$vid] = $voc->name;
  }
  $form['commentsection_vocab'] = array(
    '#type' => 'select',
    '#multiple' => FALSE,
    '#title' => t('Vocabulary'),
    '#default_value' => variable_get('commentsection_vocab', 0),
    '#options' => $vocs,
    '#description' => t('Select the vocabulary to use with commentsection nodes.'),
  );
  $form['commentsection_encode'] = array(
    '#type' => 'radios',
    '#title' => t('Charset detection'),
    '#default_value' => variable_get('commentsection_encode', 0),
    '#options' => array(0 => 'deactivated', 1 => 'activated'),
    '#description' => t('Try to detect the charset and encode in UTF-8.'),
  );
  if (module_exists('path')) {
    $form['commentsection_path'] = array(
      '#type' => 'radios',
      '#title' => t('Automatic path'),
      '#default_value' => variable_get('commentsection_path', 1),
      '#options' => array(0 => 'deactivated', 1 => 'activated'),
      '#description' => t('Automatically create a path based on the provided url.'),
    );
  }

  return system_settings_form($form);
}

