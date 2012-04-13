<?php

/**
 *Returns a count of the quantity of materials in the library
 *
 *@param $type
 *  The node type
 * @return
 *   An int representing the number quantity
 */
function dlms_stat_count($type) {
  //return db_query('SELECT * FROM {node} n WHERE type = :type', array(':type' => $type));
  //return db_query("SELECT * FROM {node} n WHERE type = 'book'");
  $query = db_select('node', 'n')
          ->fields('n', array('nid', 'title'))
          ->condition('type', $type)
          ->condition('status', 1)
          ->addTag('node_access')
          ->countQuery()
          ->execute();
  
  return $query->fetch();
 
}

/**
 * Returns the total count of materials in the library
 *
 *@param $items
 *  An array holding an array of material properties, with the 'count' key of the child array
 *  the value to sum
 * @return
 *   An int representing the number quantity
 */
function dlms_stat_total_count($items) {
  // initiallize the total
  $total = 0;
  
  foreach ($items as $item) {
    $total = $total + (int)$item['count'];
  }
  
  return $total;
  
}


/**
 * Returns a structured array formatted for input to theme_item_list
 *
 *@param $stat
 *  An array holding an array of material properties, with the 'count' key of the child array
 *  the value to sum
 * @return
 *   An array formatted as input to theme_item_list
 */
function dlms_stat_build_list_itemt($stat) {
  // initiallize the items[] array array
  $items = array();
  
  foreach ($stat as $k => $v) {
    $items[] = array(
      'data' => '<span class = "icon"></span>'
                . '<span class = "dlms-stat-material">' . $v['name'] . '</span>'
                . '<span class = "dlms-stat-count">' . $v['count'] . '</span>',
      'class' => array('dlms-stat-item', $k . '-icon'),
    );
  }
  
  return $items;
}