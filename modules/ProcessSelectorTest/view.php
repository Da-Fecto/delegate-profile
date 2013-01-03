<script>
	$(function() {
		SelectorTest = {};
		SelectorTest.pageData = <?php echo $initialData; ?>;

		$('.selectortest-tree')
		.each(function() {
			$(this).tree('loadData', [SelectorTest.pageData[$(this).attr('data-id')]]);
		});
	});
</script>

<?php
echo $inputForm;

if($usedSelector) {

	printf(_n('%d page found with selector', '%d pages found with selector', $resultCount), $resultCount);

	echo '<span class="selectortest-used-selector">';
	echo '"' . $usedSelector . '"';
	echo '</span>';

	if($resultCount > 0) {
		echo $pager;
		echo $resultTable;
		echo $pager;
	}
}
