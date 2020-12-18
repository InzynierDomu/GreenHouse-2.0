
namespace test_json
{
const String content = "{\"SSID\":\"ssid\","
"\"PASS\":\"pass\","
"\"MQTT_SERVER\":\"192.168.0.17\","
"\"MQTT_TOPIC_TEST\":\"test\","
"\"HARDWARE_CONFIGURATION\":"
	"{\"SENSOR\":\"greenhouse/sensor\","
	"\"GPIO_CONTROLLERS\":["
		"{\"ADDRES\":\"100\","
		"\"GPIOS\":["
			"{\"TYPE\":\"OUT\","
			"\"TOPIC\":\"greenhouse/pump\"},"
			"{\"TYPE\":\"IN\","
			"\"TOPIC\":\"greenhouse/floodsensor\"}"
		"]},"	
		"{\"ADDRES\":\"010\","
		"\"GPIOS\":["
			"{\"TYPE\":\"OUT\","
			"\"TOPIC\":\"greenhouse/pump\"},"
			"{\"TYPE\":\"IN\","
			"\"TOPIC\":\"greenhouse/floodsensor\"}"
		"]}"		
	"]}"
"}";
};
