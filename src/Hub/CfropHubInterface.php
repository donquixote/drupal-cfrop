<?php
declare(strict_types=1);

namespace Drupal\cfrop\Hub;

use Drupal\cfrop\Operation\OperationInterface;

interface CfropHubInterface {

  /**
   * @param array $conf
   *
   * @return \Drupal\cfrop\Operation\OperationInterface
   *
   * @throws \Drupal\cfrapi\Exception\ConfToValueException
   */
  public function confGetOperation(array $conf): OperationInterface;

}
