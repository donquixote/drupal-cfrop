<?php

use Drupal\cfrapi\Exception\ConfToValueException;
use Drupal\cfrop\Operation\OperationInterface;

/**
 * Form builder callback for 'cfrop_operation_form'.
 *
 * @param array $form
 * @param array $form_state
 *
 * @return array
 */
function cfrop_operation_form(array $form, array &$form_state) {
  unset($form);

  $form['operation'] = [
    '#title' => t('Operation'),
    /* @see \cfrplugin_element_info() */
    '#type' => 'cfrplugin',
    '#cfrplugin_interface' => OperationInterface::class,
    '#default_value' => NULL,
  ];

  $form['actions'] = ['#type' => 'actions'];
  $form['actions']['submit'] = [
    '#type' => 'submit',
    '#value' => t('Execute'),
  ];

  return $form;
}

/**
 * Form validation callback for 'cfrop_operation_form'.
 *
 * @param array $form
 * @param array $form_state
 */
function cfrop_operation_form_validate(array $form, array &$form_state) {

  $conf = $form_state['values']['operation'];

  try {
    $op = cfrop()->confGetOperation($conf);
  }
  catch (ConfToValueException $e) {
    form_set_error(
      'operation',
      t('Failed to create the operation.'));
  }
}

/**
 * Form submit callback for 'cfrop_operation_form'.
 *
 * @param array $form
 * @param array $form_state
 */
function cfrop_operation_form_submit(array $form, array &$form_state) {

  $conf = $form_state['values']['operation'];

  try {
    $op = cfrop()->confGetOperation($conf);
  }
  catch (ConfToValueException $e) {
    drupal_set_message(
      t('Failed to create the operation object.'),
      'error');
    return;
  }

  try {
    $op->execute();
  }
  catch (\Exception $e) {
    drupal_set_message(
      t('Exception thrown when executing the operation.'),
      'error');
    return;
  }

  drupal_set_message(
    t('Operation was executed.'));
}
