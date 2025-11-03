#include <WiFi.h>
#include <HTTPClient.h>

static void send_to_thingsboard_task_handler(void* parameters);
void wifi_start();
bool isPrime(uint32_t n);
static void PrimeNumber_task_handler(void* parameters);


TaskHandle_t send_to_thingsboard_task_handle;
TaskHandle_t PrimeNumber_task_handle;
QueueHandle_t PrimeNumber_Queue;


const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* accessToken = "YOUR_THINGSBOARD_DEVICE_TOKEN";
const char* server = "http://thingsboard.cloud";
String url = String(server) + "/api/v1/" + accessToken + "/telemetry";



void wifi_start() {

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    vTaskDelay(pdMS_TO_TICKS(500));
    Serial.print(".");
  }

  Serial.println("\nWiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

}


void setup() {

  BaseType_t status;

  Serial.begin(115200);

  wifi_start();

  delay(1000);


  PrimeNumber_Queue = xQueueCreate(100, sizeof(uint32_t));
  configASSERT(PrimeNumber_Queue != NULL);

  status = xTaskCreate(PrimeNumber_task_handler, "prime number task", 1024, NULL, 3, &PrimeNumber_task_handle);
  configASSERT(status == pdPASS);

  status = xTaskCreate(send_to_thingsboard_task_handler, "send to ThingsBoard", 8192, NULL, 3, &send_to_thingsboard_task_handle);
  configASSERT(status == pdPASS);
}

bool isPrime(uint32_t n)
{

    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;

    for (uint32_t i = 3; i * i <= n; i += 2)
    {
    	if (n % i == 0)
    		return false;
    }
    return true;
}

static void PrimeNumber_task_handler(void* parameters)
{

	uint32_t num = 2;

	while(1)
	{
		if (isPrime(num))
		{
			xQueueSendToBack(PrimeNumber_Queue, &num, portMAX_DELAY);
		}
		num++;
	}

}

static void send_to_thingsboard_task_handler(void* parameters)
{
  
  uint32_t uart_number;

  while (1) {

    xQueueReceive(PrimeNumber_Queue, &uart_number, portMAX_DELAY);
    
    if (WiFi.status() == WL_CONNECTED) {

      WiFiClient client;
      HTTPClient http;



      http.begin(client, url);
      http.addHeader("Content-Type", "application/json");


      String payload = "{\"prime number\":" + String(uart_number) + "}";

      int httpResponseCode = http.POST(payload);

      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);

      Serial.println(payload);

      http.end();
    } else {
      Serial.println("WiFi disconnected! Trying to reconnect...");
      wifi_start();
    }
  }

}

void loop() 
{
}
