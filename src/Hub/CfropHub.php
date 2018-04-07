<?php
declare(strict_types=1);

namespace Drupal\cfrop\Hub;

use Drupal\cfrapi\Configurator\ConfiguratorInterface;
use Drupal\cfrapi\Exception\ConfToValueException;
use Drupal\cfrop\Operation\OperationInterface;

class CfropHub implements CfropHubInterface {

  /**
   * @var \Drupal\cfrapi\Configurator\ConfiguratorInterface
   */
  private $decorated;

  /**
   * @return self
   */
  public static function create() {
    return new self(
      cfrplugin()->interfaceGetConfigurator(
        OperationInterface::class));
  }

  /**
   * @param \Drupal\cfrapi\Configurator\ConfiguratorInterface $decorated
   */
  public function __construct(ConfiguratorInterface $decorated) {
    $this->decorated = $decorated;
  }

  /**
   * @param array $conf
   *
   * @return \Drupal\cfrop\Operation\OperationInterface
   *
   * @throws \Drupal\cfrapi\Exception\ConfToValueException
   */
  public function confGetOperation(array $conf): OperationInterface {

    $candidate = $this->decorated->confGetValue($conf);

    if ($candidate instanceof OperationInterface) {
      return $candidate;
    }

    throw new ConfToValueException(
      "The configurator returned something other than an operation object.");
  }
}
