
static void parameter_synch(const char * parameters_json)
{


}


extern void sync_conf_task()
{
    bool isSyncNeedit=false;
    const char parameters_json[8000u]={0};
    while (true)
    {
        //Checking if need it a synchronization
// get method
        if (isSyncNeedit)
        {
            //read_datas from an specific place
            parameter_synch(parameters_json);

        }

    }
}
