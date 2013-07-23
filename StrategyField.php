<?php

interface StrategyField {

  public function getFields();
  public function getForm();
  public function getLabel();  
  public function submit();
  public function validate();

}
