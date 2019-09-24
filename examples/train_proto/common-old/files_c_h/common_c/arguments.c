if (argc!=4){printf("Error: The program %s takes three parameters: %s integration_time delta_t ouput_file_name\n",argv[0],argv[0]);exit(1);}
	double integration_time=strtod(argv[1], NULL);
	double delta_t= strtod(argv[2], NULL);
	const char * output_file_name= argv[3];
	long int k,steps;

	steps=ceil(integration_time/delta_t);
	double t_ini = 0.0, t_end = integration_time;
	int n_iterations;
	n_iterations = (t_end - t_ini) / delta_t;
	double start, end;
