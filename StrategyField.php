<?php

interface StrategyField {
  public function __construct($strategy_values = NULL);

  public static function getLabel();  
  public static function getDescription();
  
  public function formatter($display);
  public function getForm();
  public function validate();
}
