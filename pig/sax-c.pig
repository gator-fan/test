REGISTER '/opt/piglib/current/*.jar';
REGISTER 'pigudf.jar';

SET job.name '[adhoc][sax-click][2015-08-13]'
SET job.priority HIGH;

raw_data = load '/mvad/rawlog/dsp/2015-08-13/17.d.c.3-*' using com.twitter.elephantbird.pig.load.LzoThriftB64LinePigLoader('dsp.thrift.LogInfo');

A = FILTER raw_data BY request.requestType == 'CLICK' AND request.requester=='16';

B = FOREACH A GENERATE request.requester AS requester, clickInfo.creativeId AS creativeid, clickInfo.impressionId as impressionid, clickInfo.errorFlag as flag;

DUMP B;

