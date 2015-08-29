package com.mediav.mobilenative.tanx;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Set;


import com.mediav.ea.common.ExchangeAuditType;
import com.mediav.ea.db.DBHelper;
import com.mediav.mobilenative.tanx.TanxInteraction;

//public class TanxNativeManager extends Manager 
public class TanxNativeManager
{
	//public List<ExchangeAuditType> getCreatives(List<Long> bannerids)
	public List<ExchangeAuditType> getCreatives(List<Long> bannerids, HashMap<Long, ExchangeAuditType> pre_ea_map)
	{
		HashMap<String, CreativeParamDto> native_map = DBHelper.getNativeByExchangeId(ExchangeAuditType.ExchangeAuditItem.TANX_ID);

		//remove already in exchange_audit and get upload_list
		List<CreativeParamDto> upload_list;

		//Iterator<Entry<String, CreativeParamDto>> iter = native_map.entrySet().iterator();
		for (Map.Entry<String,CreativeParamDto> entry : native_map.entrySet()) {
		    String creative_id = entry.getKey();

			if (!pre_ea_map.containsKey(Long.parseLong(creative_id)));
			{
				//iter.remove();
				native_map.remove(Long.parseLong(creative_id));
			}
		}
		upload_list = new ArrayList<CreativeParamDto>(native_map.values());
		TanxInteraction.uploadCreativeToTanx(upload_list);
		
		List<ExchangeAuditType> eat_list = null;

	      if (upload_list!= null)
	      {
	        for (CreativeParamDto dto : upload_list)
	        {
	          ExchangeAuditType eat = TanxInteraction.paramdto2eat(dto);
	          if (eat != null)
	          {
	            eat_list.add(eat); 
	          }
	        }
	      }

		return eat_list;
	}

	public Map<String, List<ExchangeAuditType>> computeAPIUpdate(List<ExchangeAuditType> adx_result, HashMap<Long, ExchangeAuditType> mv_result)
	{
		if(adx_result == null) return null;

		List<ExchangeAuditType> pass_list   = TanxInteraction.retrievePassFromTanx();

		int count[] = {0,0,0}; //insert, update, remove
		Set<Long> adx_set = new HashSet<Long>();
		Map<String, List<ExchangeAuditType>> result = new HashMap<String, List<ExchangeAuditType>>();
		List<ExchangeAuditType> iList = new LinkedList<ExchangeAuditType>();
		List<ExchangeAuditType> uList = new LinkedList<ExchangeAuditType>();
		result.put("i", iList);
		result.put("u", uList);

		// 1. creatives just uploaded
		for (ExchangeAuditType item : adx_result)
		{
			// should not exist in pre_map, if exist, the code will be wrong
			Long bannerid = item.getBannerid();
			ExchangeAuditType pre_eat = mv_result.get(bannerid);
			if (pre_eat == null)
			{
				//generate Insert SQL
				iList.add(item);
				count[0]++;
			} 
			else 
			{
				// TODO, log error
			}
		}
		
		// 2. creatives already updated, retrieve back and only update the status
		for (ExchangeAuditType item : pass_list)
		{
			Long bannerid = item.getBannerid();
			adx_set.add(bannerid);
			ExchangeAuditType pre_eat = mv_result.get(bannerid);
			if (pre_eat != null)
			{
				if (item.getExchangestatus() != pre_eat.getExchangestatus())
				{
					//generate Update SQL
					pre_eat.setExchangestatus(item.getExchangestatus());
					pre_eat.setStatus(TanxInteraction.ExchangeStatus2Status[item.getExchangestatus()]);
					uList.add(pre_eat);
					count[1]++;
				} else if (pre_eat.getExchangestatus() == ExchangeAuditType.ExchangeStatusType.DISAPPROVED.getStatus()
						&& !pre_eat.getReason().endsWith(item.getReason()))
				{
					pre_eat.setReason(item.getReason());
					uList.add(pre_eat);
					count[1]++;
				}
			} 
			else 
			{
				// TODO, log error
			}

		}

		return result;
	}
}
