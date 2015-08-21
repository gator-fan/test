REGISTER '/opt/piglib/current/*.jar';
REGISTER 'gson-2.2.4.jar';
REGISTER 'protobuf-java-2.5.0.jar';
REGISTER 'pigudf.jar';

SET job.name '[adhoc][geniee-s-u-e][2015-07-24]'
SET job.priority HIGH;

DEFINE JsonToMap com.mediav.dsp.log.pig.JsonToMap();


--show_raw_data = load '/mvad/rawlog/dsp/2015-07-22/{*.d.s.3-*},/mvad/rawlog/dsp/2015-07-23/{*.d.s.3-*}' using com.twitter.elephantbird.pig.load.LzoThriftB64LinePigLoader('dsp.thrift.LogInfo');
--SHOW_A = FILTER show_raw_data BY request.requestType == 'SHOW' AND request.requester == '22';
--SHOW_B = FOREACH SHOW_A GENERATE showInfo.impressionId AS s_impid;
--
--bid_raw_data = load '/mvad/rawlog/dsp/2015-07-22/{*.d.u.3-*},/mvad/rawlog/dsp/2015-07-23/{*.d.u.3-*}' using com.twitter.elephantbird.pig.load.LzoThriftB64LinePigLoader('dsp.thrift.LogInfo');
--BID_A = FILTER bid_raw_data BY request.requester == '22';
--BID_B = FOREACH BID_A GENERATE request, response, FLATTEN(response.candidates);
--BID_C = FOREACH BID_B GENERATE impressionId AS u_impid, request.requestId AS u_reqid;

--extended_raw_data = load '/mvad/rawlog/dsp-extended/2015-07-22/{*.d.e.3-*},/mvad/rawlog/dsp-extended/2015-07-23/{*.d.e.3-*}' using com.twitter.elephantbird.pig.load.LzoThriftB64LinePigLoader('dsp.thrift.ExtendedData');
extended_raw_data = load '23.d.e.3-9-kf36dg.prod.mediav.com-9092-25596120534.ext.dsp.lzo' using com.twitter.elephantbird.pig.load.LzoThriftB64LinePigLoader('dsp.thrift.ExtendedData');

extended_A = FILTER extended_raw_data BY requestType == 'REQUEST' and requester == '22';
extended_B = FOREACH extended_A GENERATE requestId, JsonToMap(data) AS data;
extended_C = FOREACH extended_B GENERATE requestId as e_reqid, data#'zoneid' AS zoneid;

--result1 = JOIN SHOW_B by (s_impid), BID_C By (u_impid);
--result2 = JOIN result1 by (u_reqid), extended_C By (e_reqid);

--DUMP result2;
DUMP extended_C;
