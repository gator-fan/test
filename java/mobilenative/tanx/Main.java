package com.mediav.mobilenative.tanx;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

import com.mediav.ea.common.ExchangeAuditType;
import com.mediav.ea.db.DBHelper;

public class Main
{
	/**
	 * @param args
	 */
	public static void main(String[] args)
	{
		HashMap<Integer, HashMap<Long, ExchangeAuditType>> pre_ea_map = DBHelper.getExchangeAuditByExchange(ExchangeAuditType.ExchangeAuditItem.TANX_ID);

		List<Long> bannerids = null;
		TanxNativeManager manager = new TanxNativeManager();

		List<ExchangeAuditType> eat_list = manager.getCreatives(bannerids, pre_ea_map.get(ExchangeAuditType.ExchangeAuditItem.TANX_ID));

		Map<String, List<ExchangeAuditType>> updates = manager.computeAPIUpdate(eat_list, pre_ea_map.get(ExchangeAuditType.ExchangeAuditItem.TANX_ID));
		DBHelper.executeEAAPI(updates);
	}

}
