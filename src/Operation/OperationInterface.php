<?php
declare(strict_types=1);

namespace Drupal\cfrop\Operation;

interface OperationInterface {

  /**
   * Runs the operation. Returns nothing.
   */
  public function execute();

}
