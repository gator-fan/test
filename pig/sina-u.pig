REGISTER '/opt/piglib/current/*.jar';
REGISTER 'pigudf.jar';

SET job.name '[adhoc][max-bid][2015-06-01]'
SET job.priority HIGH;

DEFINE Check com.mediav.dsp.log.pig.Check('8214091');
DEFINE StringMatch com.mediav.dsp.log.pig.StringMatch();
DEFINE CheckLongIn com.mediav.dsp.log.pig.CheckLongIn('674853132555131404,2604993515004191404');

--u_data = load '/mvad/rawlog/dsp/2015-06-03/{18.d.u.3.m-*pc*,19.d.u.3.m-*pc*}' using com.twitter.elephantbird.pig.load.LzoThriftB64LinePigLoader('dsp.thrift.LogInfo');
--u_data = load '18.d.u.3-9-kf35dg.prod.mediav.com-9092-5538947734.pc.dsp.lzo' using com.twitter.elephantbird.pig.load.LzoThriftB64LinePigLoader('dsp.thrift.LogInfo');
--u_data = load '14.d.u.3-9-kf35dg.prod.mediav.com-9092-5616805715.pc.dsp.lzo' using com.twitter.elephantbird.pig.load.LzoThriftB64LinePigLoader('dsp.thrift.LogInfo');
--u_data = load '13.d.u.3-9-kf35dg.prod.mediav.com-9092-5896133530.pc.dsp.lzo' using com.twitter.elephantbird.pig.load.LzoThriftB64LinePigLoader('dsp.thrift.LogInfo');

u_data = load '/mvad/rawlog/dsp/2015-06-24/{11.d.u.3-*, 13.d.u.3-*, 15.d.u.3-*, 17.d.u.3-*, 19.d.u.3-*, 21.d.u.3-*}' using com.twitter.elephantbird.pig.load.LzoThriftB64LinePigLoader('dsp.thrift.LogInfo');


A = FILTER u_data BY request.requester=='16';

B = FOREACH A GENERATE FLATTEN(response.candidates.solutionId) AS solutionid, FLATTEN(response.candidates.creativeId) AS creativeid, FLATTEN(response.candidates.advertiserId) AS advertiserid;

C = FILTER B BY solutionid == 10338702;

DUMP C;


--E = FILTER B BY CheckLongIn(impid) == 1;
--solutionid=10338702

--e_data = load '/mvad/rawlog/dsp-extended/2015-06-01/{15.d.e.*,16.d.e.*}' using com.twitter.elephantbird.pig.load.LzoThriftB64LinePigLoader('dsp.thrift.ExtendedData');
--A = FILTER u_data BY request.requester=='20' and StringMatch('www.360kan.com', response.publisherUrl) == 1;
--B = FOREACH A GENERATE request, response, FLATTEN(response.candidates);
--C = FOREACH u_data GENERATE COUNT(response.candidates);
--DUMP C;
--B = FOREACH u_data GENERATE FLATTEN(bidRequestInfo.adspaceInfo.width) AS width, FLATTEN(bidRequestInfo.adspaceInfo.height) AS height, 1 AS num;
--B = FOREACH u_data GENERATE FLATTEN(bidRequestInfo.adspaceInfo.adspaceId) AS adspaceid, FLATTEN(response.candidates.solutionId) AS solutionid;

--B = FOREACH u_data GENERATE FLATTEN(response.candidates.solutionId) AS solutionid, response.requestId;
--B = FOREACH A GENERATE FLATTEN(response.candidates.solutionId) AS solutionid, request.requestId;
--C = FILTER u_data BY request.requestId == 1756450049780348802l;
--C = FILTER B BY impressionId == 47643464455000305l;
--C = FILTER B BY advertiserId == 71776;
--DUMP C;
--E = GROUP B BY (width, height);
--C = FILTER B BY adspaceid == 1034455 and solutionid == 9495378;

--C = FILTER B BY solutionid == 10307446 or solutionid == 10307452;
--C = FILTER B BY creativeid == 47628085 or creativeid == 47847708;
--result = FOREACH E GENERATE FLATTEN(group) AS (width, height), SUM(B.num) AS num;
--C = FILTER B BY CheckLongIn(impressionId) == 1;
--C = FILTER B BY Check(adspaceId) == 1;
