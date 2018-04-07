<?php
declare(strict_types=1);

namespace Drupal\cfrop_example\Operation;

use Drupal\cfrop\Operation\OperationInterface;

/**
 * @CfrPlugin("hello", "Hello world")
 */
class Operation_Hello implements OperationInterface {

  /**
   * Runs the operation. Returns nothing.
   */
  public function execute() {
    drupal_set_message(
      t('Hello world'));
  }
}
