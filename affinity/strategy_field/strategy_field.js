
(function ($) {

Drupal.behaviors.strategy_field = {
  attach: function (context, settings) {
    // On page load the select list hasn't been changed
   $(".strategy_field_remove").click(function () {
      var strategy_name = $(this).data('class');
      var strategy_delta = $(this).data('delta');
      if (confirm("Are you sure you want to remove this " + strategy_name + "?") == true) {
        $(this).siblings("input.strategy-class").val('');
        $(this).closest("tr").hide();
      }
    });
  }
}})(jQuery);
