REGISTER '/opt/piglib/current/*.jar';
REGISTER 'gson-2.2.4.jar';
REGISTER 'protobuf-java-2.5.0.jar';
REGISTER 'pigudf.jar';

SET job.name '[adhoc][sina-e][2015-08-19]'
SET job.priority HIGH;

--no creative
--DEFINE CheckLongIn com.mediav.dsp.log.pig.CheckLongIn('1594322249523891671,1594322249533361975,1594322249643817439,1765459035494973036,1355631469420670199,1589818650246126510,1594322249939430468');
--DEFINE PROTO_TO_TUPLE com.mediav.proto.pig.ProtobufBytesToTuple('com.mediav.dsp.google.adx.RealtimeBidding.BidRequest');
--DEFINE PROTO_TO_TUPLE com.mediav.proto.pig.ProtobufBytesToTuple('com.mediav.dsp.sina.adx.RealtimeBidding.BidRequest');

DEFINE JsonToMap com.mediav.dsp.log.pig.JsonToMap();

--raw_data = load '/mvad/rawlog/dsp-extended/2015-08-17/*.d.e.3-*' using com.twitter.elephantbird.pig.load.LzoThriftB64LinePigLoader('dsp.thrift.ExtendedData');
raw_data = load '../../wangfan/15.d.e.3-9-kf36dg.prod.mediav.com-9092-29071996604.ext.dsp.lzo' using com.twitter.elephantbird.pig.load.LzoThriftB64LinePigLoader('dsp.thrift.ExtendedData');


A = FILTER raw_data BY requestType == 'REQUEST' and requester == '16';

--B = FOREACH A GENERATE requestId, data, PROTO_TO_TUPLE(data) AS request;
--B = FOREACH A GENERATE requestId, data, PROTO_TO_TUPLE(data) AS request;
B = FOREACH A GENERATE data AS origin, JsonToMap(data) AS data;
DUMP B;

--C = FILTER B BY data#'imp.banner.w'== 0 AND data#'imp.banner.h' == 10;
--C = FILTER B BY data#'imp.banner.w' != 300 OR data#'imp.banner.w' != 950;

--DUMP C;

--C = FOREACH B GENERATE requestId, FLATTEN(request.adslot.excluded_attribute_bag) AS attribute, data;

--E = FILTER C BY CheckLongIn(requestId) == 1;

--DUMP E


--no creative in big
--DEFINE CheckLongIn com.mediav.dsp.log.pig.CheckLongIn('1409669135307877193,1580805940614010162');
--DEFINE PROTO_TO_TUPLE com.mediav.proto.pig.ProtobufBytesToTuple('MAXPrivate.MaxBiddingPrivate.BidRequest');
--raw_data = load '14.d.e.3-9-kf36dg.prod.mediav.com-9092-20486699643.ext.dsp.lzo' using com.twitter.elephantbird.pig.load.LzoThriftB64LinePigLoader('dsp.thrift.ExtendedData');
--raw_data = load '/mvad/rawlog/dsp-extended/2015-06-14/{14.d.e.3-*,15.d.e.3-*}' using com.twitter.elephantbird.pig.load.LzoThriftB64LinePigLoader('dsp.thrift.ExtendedData');
--B = FOREACH A GENERATE requestId, data AS request;
--C = FOREACH B GENERATE requestId, FLATTEN(request.adslot.excluded_attribute_bag) AS attribute, data, 1 AS num;
--D = FOREACH C GENERATE requestId, FLATTEN(attribute) AS attribute, data;
--E = FILTER D BY attribute == 48 and CheckLongIn(requestId) == 1;
--C = FILTER B BY CheckLongIn(requestId) == 1;
--E = FILTER C BY CheckLongIn(requestId) == 1;
--F = FOREACH E GENERATE requestId, attribute, data, 1 AS num;
--G = FOREACH F GENERATE requestId, attribute, data, SUM(E.num) AS num;
--DUMP G;
--fan
--E = FILTER D BY attribute == 48 and CheckLongIn(requestId) == 1;
--F = FOREACH E GENERATE requestId, attribute, data, 1 AS num;
--G = FOREACH F GENERATE requestId, attribute, data, SUM(E.num) AS num;
--DUMP G;
--E = FILTER B BY CheckLongIn(requestId) == 1;
--DUMP E;
--C = FOREACH B GENERATE request.mv_user_id, request.page_uid, 1 AS num;
--D = GROUP C BY (mv_user_id,page_uid);
--E = FOREACH D GENERATE FLATTEN(group), SUM(C.num) AS num;
--result = ORDER E BY num DESC;
----C = FOREACH B GENERATE requestId, data.id;
--DUMP result;
