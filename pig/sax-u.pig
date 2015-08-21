REGISTER '/opt/piglib/current/*.jar';
REGISTER 'pigudf.jar';

SET job.name '[adhoc][sax-bid][2015-08-14]'
SET job.priority HIGH;

u_data = load '/mvad/rawlog/dsp/2015-08-14/11.d.u.3-*' using com.twitter.elephantbird.pig.load.LzoThriftB64LinePigLoader('dsp.thrift.LogInfo');


A = FILTER u_data BY request.requestType == 'REQUEST' AND request.requester=='16';

B = FOREACH A GENERATE FLATTEN(response.candidates.auctionPrice) AS auctionPrice, FLATTEN(response.candidates.creativeId) AS creativeid, FLATTEN(response.candidates.width) AS width, FLATTEN(response.candidates.height) AS height;

DUMP B;
