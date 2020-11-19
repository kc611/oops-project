class DataPoint{
    public:
        double x,y;

        DataPoint(double x,double y){
            this->x = x;
            this->y = y;
        }
};

class DataSet{
    friend class Curve_fitter;
    private:
        vector<DataPoint> points;
    public:
        int num_datapoints;

        DataSet(){

        };

        DataSet(int num_points){
            num_datapoints=num_points;

            cout<<"Enter number of data points : ";
            cin>>num_datapoints;
            for(int i=0;i<num_datapoints;i++){
                double temp1,temp2;
                cout<<"Enter datapoint number "<<i+1<<" : ";
                cin>>temp1>>temp2;
                DataPoint new_point = DataPoint(temp1,temp2);
                points.push_back(new_point);
            }

        }

        DataSet(string filename){
            num_datapoints=0;
            ifstream raw_data;
            raw_data.open(filename);
            if(!raw_data){
                cout<<"File does not exist or is corrupted"<<endl;
            }

            double x,y;

            while(raw_data>>x>>y) {
                DataPoint new_point = DataPoint(x,y);
                points.push_back(new_point);
                num_datapoints++;
            }
        }
};
