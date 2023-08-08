
import sys
import pickle
import json
import pandas as pd
import numpy as np

import pickle
import json
from scipy.sparse import csc_matrix

def convert_to_json(pickle_file, json_file):
    # Load the pickle file using 'latin1' encoding
    with open(pickle_file, 'rb') as file:
        data = pickle.load(file, encoding='latin1')

    def convert_csc_matrices(obj):
        if isinstance(obj, csc_matrix):
            return obj.toarray().tolist()  # Convert to list
        elif isinstance(obj, np.ndarray):
            return obj.tolist()  # Convert to list
        elif isinstance(obj, list):
            return [convert_csc_matrices(e) for e in obj]
        elif isinstance(obj, dict):
            return {key: convert_csc_matrices(value) for key, value in obj.items()}
        else:
            return obj

    data_converted = convert_csc_matrices(data)

    # Write the data to a JSON file
    with open(json_file, 'w') as file:
        json.dump(data_converted, file, indent=4)



def main(args):
    filename = "basicModel_f_lbs_10_207_0_v1.0.0.pkl"

    # Convert the pickle file to JSON
    # convert_to_json(filename, filename+"new.json")

    # Load the pickle format file
    # with open(filename, 'rb') as f:
        # new_dict = pickle.load(f,encoding='latin1')

    df = pd.read_pickle(filename)
    print(df)

    # json_list = df.to_json(orient='records')
    # json_list = json.loads(json.dump(df))

    model_data_np = {}
    for k in df.keys():
        print(k)
        if(k=='J_regressor'):
            model_data_np[k]=np.require((df[k].toarray()),dtype=np.float32,requirements=['C']).tolist()
        else:
            try:
                if k=='f' or k=='kintree_table':
                    model_data_np[k]=np.require((df[k]),dtype=np.int32,requirements=['C']).tolist()
                else:
                    model_data_np[k]=np.require((df[k]),dtype=np.float32,requirements=['C']).tolist()
            except:
                print('skipped '+ k)

    json_list = json.loads(json.dumps(model_data_np))
    with open(
            filename + '.json',
            'w',
            encoding='utf-8'
        ) as outfile:
        json.dump(json_list, outfile, ensure_ascii=False, indent=4)



if __name__ == '__main__':
    #if sys.version_info[0] != 2:
    #    raise EnvironmentError('Run this file with Python2!')

    main(sys.argv)