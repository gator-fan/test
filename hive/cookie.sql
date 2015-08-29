select count ( distinct cookie ) from mediav_base.d_clickvalue where date = '2015-07-29' and adspace_id = 37938;

select advertiser_id,click_count,order_count from mediav_base.d_clickvalue where date = '2015-07-29' and click_count > 0 and order_count > 0 order by order_count/click_count limit 3;
