#include "fnnlib.hpp"
#include <cmath>
#include <cstdlib>

int main ()
{
    printf ("1\n");
	


	Layer** layers = new Layer*[3];
	layers[0] = new Layer (1);
	layers[1] = new Layer (10, ActivationFunction::TANH);
	layers[2] = new Layer (1);

	BPTT bptt_alg (20000, 11, 0.05, 0.0);
	RNN* net = new RNN (3, layers, &bptt_alg);
	
	RandomInitialization rand_init (-0.1, 0.1);
	net->ConnectLayerToLayer (0, 1, &rand_init, true);
	net->ConnectLayerToLayer (1, 1, &rand_init, true);
	net->ConnectLayerToLayer (1, 2, &rand_init, true);

	FileDataSource ds_in (100, 1, "data.txt");
	FileDataSource ds_out (100, 1, "out.txt");

	net->SetInput (0, 0, &ds_in);
	net->SetOutput (0, 2, &ds_out, false);    

	net->Train ();

	NetworkErrorData* ed = net->Test (2, 100, 1, false);
	cout << "MSE: " << ed->GetLayerData (2)->GetMse () << endl;
	
	FILE * f = fopen ("rnn_output.txt", "w");
	arma::vec temp(1);
	for (int i = 0; i < 100; i ++) fprintf (f, "%d %f %f\n", i, (ed->GetLayerData(2)->GetPairAt(i, &temp), temp[0]), (ed->GetLayerData(2)->GetPairAt(i, &temp), temp[1]));
	fclose (f);

	delete layers[1];
	delete layers[2];
	delete layers[0];
	delete []layers;
	//delete net;

	return 0;
}
