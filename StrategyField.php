<?php

interface StrategyField {

  public function getFields();
  public function getForm();
  public static function getLabel();  
  public function submit();
  public function validate();
  public function __construct($strategy_values = NULL);
}
