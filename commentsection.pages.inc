<?php
// $Id$

/**
 * Automatically create a node for a given URL
 */
function commentsection_page() {
  global $user;

  //craft url
  $url_base = variable_get('commentsection_base', '');
  for ($i=2;arg($i);$i++) {
    $url_alias .= '/'. check_plain(arg($i));
  }
  $url_base .= $url_alias;
  $url_source = str_replace(variable_get('commentsection_base', ''), variable_get('commentsection_source', ''), $url_base);

  //check for node in case of changed/unset path
  if ($node = db_fetch_object(db_query("SELECT nid FROM {commentsection} WHERE url='%s'", $url_base))) {
    drupal_goto('node/'. $node->nid);
    exit;
  }



  $data = drupal_http_request($url_source);
  if ($data->code == '200') {
    $xml = commentsection_parse_xml($data->data);
    if (!($xml['indicator'] == 'yes' OR $xml['indicator'] == '1')) {

      drupal_not_found();
      exit;
    }
  }
  else {
    drupal_not_found();
    exit;
  }

  $node->type   = 'commentsection';
  $node->title  = $encoding ? commentsection_encode($xml['title']) : $xml['title'];
  $node->teaser = $encoding ? commentsection_encode($xml['body']) : $xml['body'];
  $node->body   = $encoding ? commentsection_encode($xml['body']) : $xml['body'];
  $node->body  .= $encoding ? '<p class="commentsection_author">'. commentsection_encode($xml['byline']) .'</p>' : '<p class="commentsection_author">'. $xml['byline'] .'</p>';

  //Craft date
  $date = $xml['date'];
  if (substr($date, 2, 1) != '.') $date = '0'. $date;
  if (substr($date, 5, 1) != '.') $date = substr($date, 0, 3) .'0'. substr($date, 3, strlen($date));
  $date = substr($date, 6, 4) .'-'. substr($date, 3, 2) .'-'. substr($date, 0, 2) .' '. substr($date, (strlen($date)-5), strlen($date));
  $date = strtotime($date);
  //   $date = format_date($date, 'custom', 'Y-m-d H:i:s O');
  $node->created = $date;
  $node->url = $url_base;
  $node->path = 'commentsection/url'. $url_alias;

  $node_options  = variable_get('node_options_commentsection', array());
  $node->status  = in_array('status', $node_options)  ? 1 : 0;
  $node->promote = in_array('promote', $node_options) ? 1 : 0;
  $node->sticky  = in_array('sticky', $node_options)  ? 1 : 0;
  $node->comment = variable_get('comment_commentsection', 2);
  $node->format  = FILTER_FORMAT_DEFAULT;

  //TODO: define user
  if (variable_get('commentsection_original_author', FALSE)) {
    $author = user_load(array('name' => ($encoding ? commentsection_encode($xml['author']) : $xml['author'])));
  }
  if (($authorname = variable_get('commentsection_default_author', NULL)) AND !$author->uid) {
    $author = user_load(array('name' => $authorname));
  }
  $node->uid     = $author->uid ? $author->uid : 0;

  //remember user
  //   $account = $user;
  //switch to admin account
  //   $user = user_load(array('uid' => 1));
  //save node
  node_save($node);
  //save taxonomy
  taxonomy_node_save($node->nid, $terms);
  if (is_array($xml['taxonomy'])) {
    foreach ($xml['taxonomy'] as $value) {
      $taxonomy .= $encoding ? commentsection_encode($value) : $value;
      $taxonomy .= ',';
    }
  }
  $taxonomy = substr($taxonomy, 0, (strlen($taxonomy)-1));
  if ($vid = variable_get('commentsection_vocab', 0)) {
    $terms['tags'] = array($vid => $taxonomy);
    taxonomy_node_save($node->nid, $terms);
  }

  //set path alias
  if (module_exists('commentrss')) {
    path_set_alias('crss/node/'. $node->nid, 'crss/commentsection/url'. $url_alias);
  }

  //goto new node
  if ($node) {
    drupal_goto('node/'. $node->nid);
  }
  else {
    drupal_not_found();
  }

  exit;
}

