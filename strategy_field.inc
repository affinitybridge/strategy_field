<?php
/**
 * @file
 * strategy_field.inc
 */

/**
 * Helper function to update field revision rows in the DB.
 */
function strategy_field_update_revisions($field_name, $class_name, $update_settings = array(), $update_class_name = '') {
  $updated_revisions = array();
  $prefixes = array(
    'field_data_',
    'field_revision_',
  );
  foreach ($prefixes as $prefix) {
    $table_name = $prefix . $field_name;
    $class_column = $field_name . '_class';
    drupal_set_message(
      t('Updating table @table-name', array('@table-name' => $table_name))
    );
    $field_rows = db_query(
      sprintf(
        'SELECT * FROM %s WHERE %s = \'%s\'',
        $table_name,
        $class_column,
        $class_name
      )
    )->fetchAllAssoc('revision_id');
    foreach ($field_rows as $revision_id => $row) {
      drupal_set_message(
        t(
          'Updating revision @revision-id (delta @delta) of @bundle @entity-type @entity-id',
          array(
            '@revision-id' => $revision_id,
            '@delta' => $row->delta,
            '@bundle' => $row->bundle,
            '@entity-type' => $row->entity_type,
            '@entity-id' => $row->entity_id
          )
        )
      );
      $update_fields = array();
      if ($update_settings) {
        $settings_column = $field_name . '_strategy_settings';
        $current_settings = unserialize($row->{$settings_column});
        if (empty($current_settings)) {
          $current_settings = array();
        }
        if (!is_array($current_settings)) {
          $current_settings = unserialize($current_settings);
        }
        $update_fields[$settings_column] = serialize(
          array_merge($current_settings, $update_settings)
        );
      }
      if ($update_class_name) {
        $update_fields[$class_column] = $update_class_name;
      }
      db_update($table_name)
      ->fields($update_fields)
      ->condition('revision_id', $revision_id)
      ->condition('delta', $row->delta)
      ->execute();
      $updated_revisions[] = $revision_id;
    }
  }
  return $updated_revisions;
}
