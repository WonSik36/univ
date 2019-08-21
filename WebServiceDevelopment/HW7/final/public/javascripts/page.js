// not completed
/*
function Page(pageNum,listNum=10,b_pageNum_listNum=10){
	var pageNum = pageNum;
	var list = listNum;
	var b_pageNum_list = b_pageNum_listNum;
	var block = Math.ceil(pageNum/b_pageNum_list);
	var b_start_page = (block-1)*b_pageNum_list+1;
	var b_end_page = b_start_page + b_pageNum_list - 1;
	var total_page = Math.ceil(total_count/list);
	var total_block = Math.ceil(total_page/b_pageNum_list);
	if(b_end_page > total_page) b_end_page=total_page;
}

Page.prototype.makeTable(tclass){

}

Page.prototype.makePage(tclass){

}
/* page button tags
<ul class="pagination center-block" style="width:300px">
			    <li>
			      <a href="#" aria-label="Previous">
			        <span aria-hidden="true">&laquo;</span>
			      </a>
			    </li>
			    <li><a href="#">1</a></li>
			    <li><a href="#">2</a></li>
			    <li><a href="#">3</a></li>
			    <li><a href="#">4</a></li>
			    <li><a href="#">5</a></li>
			    <li>
			      <a href="#" aria-label="Next">
			        <span aria-hidden="true">&raquo;</span>
			      </a>
			    </li>
			  </ul>
*/