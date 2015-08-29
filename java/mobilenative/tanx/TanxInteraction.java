package com.mediav.mobilenative.tanx;

import java.text.SimpleDateFormat;
import java.util.Collections;
import java.util.Date;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import org.apache.commons.lang.StringUtils;
import org.codehaus.jackson.type.TypeReference;

import com.baidu.es.demo.util.JsonUtils;
import com.mediav.ea.common.EATBuilder;
import com.mediav.ea.common.ExchangeAuditType;
import com.mediav.ea.common.LogHelper;
import com.mediav.ea.config.ConfigHelper;
import com.mediav.ea.tanx.CreativeDto;
import com.tanx.Util;

public class TanxInteraction 
{
  private static final String PASS_STATUS = "PASS";
  private static final String WAITING_STATUS = "WAITING";
  private static final String REFUSE_STATUS = "REFUSE";
  private static final Integer PAGE_SIZE = 1000;
  
  public static final String CREATIVE_AUDIT_RESPONSE_REGEX = "\"creative_dto\":(\\[.*\\])"; 
  
  /*
   * definition of exchangestatus in tanx: 0(WAITING), 1(PASS), 2(REFUSE)
   * mapping from exchangestatus to status: 
   *                                         0 => 0
   *                                         1 => 1
   *                                         2 => 0
   */
  public static final int ExchangeStatus2Status[] = {0,1,0};
  
  private static final Map<String, Integer> TANX_STATUS_MAP = createMap();
  
  private static Map<String, Integer> createMap()
  {
    Map<String, Integer> aMap = new HashMap<String, Integer>();
    aMap.put(PASS_STATUS, 1);
    aMap.put(REFUSE_STATUS, 2);
    aMap.put(WAITING_STATUS, 0);
    return Collections.unmodifiableMap(aMap);
  }

  public static List<CreativeDto> string2List(String body)
  {
    List<CreativeDto> result = null;
    Pattern p = Pattern.compile(CREATIVE_AUDIT_RESPONSE_REGEX);
    Matcher m = p.matcher(body);
    String json_str = null;
    if (m.find())
    {
      json_str = m.group(1);
      result = JsonUtils.json2GenericObject(json_str, new TypeReference<List<CreativeDto>>(){});
      LogHelper.getInstance().debug("ListSize:" + String.valueOf(result.size()));
    }
    return result;
  }
  
  public static ExchangeAuditType dto2eat(CreativeDto dto)
  {
    ExchangeAuditType result = null;
    if (dto != null && TANX_STATUS_MAP.containsKey(dto.getStatus()))
    {
      if (StringUtils.isNumeric(dto.getCreative_id()))
      {
        int exchangestatus = TANX_STATUS_MAP.get(dto.getStatus());
        result = new EATBuilder().bannerid(Long.parseLong(dto.getCreative_id())).exchangeid(ExchangeAuditType.ExchangeAuditItem.TANX_ID)
            .status(ExchangeStatus2Status[exchangestatus]).exchangestatus(exchangestatus)
            .reason(dto.getRefuse_cause()).build();
      }
      else
      {
        LogHelper.getInstance().error(dto.toString());
      }
    }
    return result;
  }

  public static ExchangeAuditType paramdto2eat(CreativeParamDto dto)
  {
    ExchangeAuditType result = null;
    if (dto != null)
    {
      if (StringUtils.isNumeric(dto.getCreative_id()))
      {
        result = new EATBuilder().bannerid(Long.parseLong(dto.getCreative_id())).exchangeid(ExchangeAuditType.ExchangeAuditItem.TANX_ID)
            .status(0).exchangestatus(0)
            .reason("").build();
      }
      else
      {
        LogHelper.getInstance().error(dto.toString());
      }
    }
    return result;
  }

  public static List<ExchangeAuditType> retrievePassFromTanx()
  {
    List<ExchangeAuditType> result = new LinkedList<ExchangeAuditType>();
    boolean flag = true;
    Integer page = 1;
    while (flag)
    {
      TreeMap<String, String> apiparamsMap = new TreeMap<String, String>();
      apiparamsMap.put("format", "json");
      apiparamsMap.put("method", "taobao.tanx.creatives.get");
      apiparamsMap.put("sign_method", "md5");
      apiparamsMap.put("app_key", ConfigHelper.getInstance().getTanx_appkey());
      apiparamsMap.put("v", "2.0");
      String timestamp = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss")
          .format(new Date());
      apiparamsMap.put("timestamp", timestamp);
      long t = System.currentTimeMillis() / 1000;
      apiparamsMap.put("member_id",
          String.valueOf(ConfigHelper.getInstance().getTanx_dspid()));
      apiparamsMap.put("token",
          Util.md5(ConfigHelper.getInstance().getTanx_dspkey() + t));
      apiparamsMap.put("sign_time", String.valueOf(t));
      //apiparamsMap.put("status", REFUSE_STATUS);
      apiparamsMap.put("status", PASS_STATUS);
      apiparamsMap.put("page", String.valueOf(page));

      // signature
      String sign = Util.md5Signature(apiparamsMap, ConfigHelper.getInstance()
          .getTanx_appsecret());
      apiparamsMap.put("sign", sign);
      StringBuilder param = new StringBuilder();
      for (Iterator<Map.Entry<String, String>> it = apiparamsMap.entrySet()
          .iterator(); it.hasNext();)
      {
        Map.Entry<String, String> e = it.next();
        param.append("&").append(e.getKey()).append("=").append(e.getValue());
      }

      String body = Util.getResult(ConfigHelper.getInstance().getTanx_apiurl(),
          param.toString().substring(1));
      //System.out.println(body);

      List<CreativeDto> dto_list = string2List(body);

      if (dto_list != null)
      {
        for (CreativeDto dto : dto_list)
        {
          ExchangeAuditType eat = dto2eat(dto);
          if (eat != null)
          {
            result.add(eat); 
          }
        }
      }

      if (dto_list == null || dto_list.size() < PAGE_SIZE)
      {
        flag = false;
      } else
      {
        page++;
      }
      //test
      //flag = false;
    }
    
    return result;
  }
  
  /**
   * @param list of creatives to be uploaded
   * @return successful upload operation
   */
  public static void uploadCreativeToTanx(List<CreativeParamDto> creative_param_dtos)
  {
	for (CreativeParamDto dto : creative_param_dtos)
	{
      TreeMap<String, String> apiparamsMap = new TreeMap<String, String>();
      apiparamsMap.put("format", "json");
      apiparamsMap.put("method", "tanx.service.audit.creatives.add");
      apiparamsMap.put("sign_method", "md5");
      apiparamsMap.put("app_key", ConfigHelper.getInstance().getTanx_appkey());
      apiparamsMap.put("v", "2.0");
      String timestamp = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss")
          .format(new Date());
      apiparamsMap.put("timestamp", timestamp);
      long t = System.currentTimeMillis() / 1000;
      apiparamsMap.put("member_id",
          String.valueOf(ConfigHelper.getInstance().getTanx_dspid()));
      apiparamsMap.put("token",
          Util.md5(ConfigHelper.getInstance().getTanx_dspkey() + t));
      apiparamsMap.put("sign_time", String.valueOf(t));
      apiparamsMap.put("creative", dto.toString());

      // signature
      String sign = Util.md5Signature(apiparamsMap, ConfigHelper.getInstance()
          .getTanx_appsecret());
      apiparamsMap.put("sign", sign);

      StringBuilder param = new StringBuilder();
      for (Iterator<Map.Entry<String, String>> it = apiparamsMap.entrySet()
          .iterator(); it.hasNext();)
      {
        Map.Entry<String, String> e = it.next();
        param.append("&").append(e.getKey()).append("=").append(e.getValue());
      }

      String body = Util.getResult(ConfigHelper.getInstance().getTanx_apiurl(),
          param.toString().substring(1));
      System.out.println(body);
      // TODO, how to handle result
    }
  }
  
}
