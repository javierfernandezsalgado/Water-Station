#define PIN_FLAG 12


extern set_status(status_led_str status)
{
  switch (status)
    {
    case nominal:
      {
        break;
      }
    case configuration:
      {
        break;
      }
    case error:
      {
        break;
      }
    defaulf:
      {
        assert (true);
        break;
      }

    }
}

extern set_up_led_status()
{



}

