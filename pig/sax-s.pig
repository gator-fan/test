REGISTER '/opt/piglib/current/*.jar';
REGISTER 'pigudf.jar';

SET job.name '[adhoc][sax-s.pig][2015-08-13]'
SET job.priority HIGH;

raw_data = load '/mvad/rawlog/dsp/2015-08-14/11.d.s.3-*' using com.twitter.elephantbird.pig.load.LzoThriftB64LinePigLoader('dsp.thrift.LogInfo');

A = FILTER raw_data BY request.requestType == 'SHOW' AND request.requester=='16';

B = FOREACH A GENERATE request.requester AS requester, showInfo.creativeId AS creativeid, showInfo.impressionId as impressionid, showInfo.winPrice as price, showInfo.errorFlag as flag;

DUMP B;

