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