<?php

use Drupal\cfrapi\Exception\ConfToValueException;
use Drupal\cfrop\Operation\OperationInterface;

require_once __DIR__ . '/cfrop.pages.operation_form.inc';

/**
 * Form builder callback for 'cfrop_operation_form'.
 *
 * @param array $form
 * @param array $form_state
 *
 * @return array
 */
function cfrop_themeop_form(array $form, array &$form_state) {
  $form = cfrop_operation_form($form, $form_state);

  $options = [];
  foreach (list_themes() as $theme_name => $theme_object) {
    if (!$theme_object->status) {
      continue;
    }
    $options[$theme_name] = $theme_object->info['name'];
  }

  $form['theme'] = [
    '#title' => t('Theme'),
    '#type' => 'select',
    '#options' => $options,
    '#weight' => -10,
  ];

  if (isset($_GET['theme'])) {
    $selected_theme = $_GET['theme'];
    if (isset($options[$selected_theme])) {
      $form['theme']['#default_value'] = $selected_theme;
    }
  }

  return $form;
}

/**
 * Form validation callback for 'cfrop_operation_form'.
 *
 * @param array $form
 * @param array $form_state
 */
function cfrop_themeop_form_validate(array $form, array &$form_state) {
  cfrop_operation_form_validate($form, $form_state);
}

/**
 * Form submit callback for 'cfrop_operation_form'.
 *
 * @param array $form
 * @param array $form_state
 */
function cfrop_themeop_form_submit(array $form, array &$form_state) {

  $theme_objects = list_themes();
  $active_theme = $GLOBALS['theme'];
  if (!isset($theme_objects[$active_theme])) {
    // Something strange happened.
    drupal_set_message(
      t(
        'Theme for this operation: @theme',
        ['@theme' => t('N/A')]));
  }
  elseif (!isset($theme_objects[$active_theme]->info['name'])) {
    drupal_set_message(
      t(
        'Theme for this operation: @theme',
        ['@theme' => $active_theme]));
  }
  else {
    drupal_set_message(
      t(
        'Theme for this operation: @theme',
        ['@theme' => $theme_objects[$active_theme]->info['name']]));
  }

  cfrop_operation_form_submit($form, $form_state);

  $selected_theme = $form_state['values']['theme'];
  $form_state['redirect'][1]['query']['theme'] = $selected_theme;
}
