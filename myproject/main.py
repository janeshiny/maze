from flask import Flask, render_template, request
import numpy as np
import os
from tensorflow.keras import models
from tensorflow.keras.models import load_model
from tensorflow.keras.preprocessing import image
from tensorflow.keras.applications.inception_v3 import preprocess_input
from PIL import Image
from werkzeug.utils import secure_filename
from tensorflow.keras.applications.vgg16 import VGG16, preprocess_input, decode_predictions


app = Flask(__name__,template_folder='E:\\other\\nm\\myproject\\templates')

@app.route('/')
def index():
    return render_template('Homepage.html')

@app.route('/about')
def about():
    return render_template('aboutus.html')

@app.route('/predict')
def predict():
    return render_template('prediction.html')

# @app.route('/process', methods=['POST'])
# def process():
#     """
#     f=request.files['image']
#     basepath=os.path.dirname(__file__)
#     filepath=os.path.join(basepath,'uploads',f.filename)
#     f.save(filepath)

#     img=image.load_img(filepath,target_size(224,224))
#     x=image.img_to_array(img)
#     x=np.expand_dims(x,axis=0)
#     img_data=preprocess_input(x)
#     result=np.argmax(modeln.predict(img_data))
#     result = "Tea leaf disease prediction result"
#     return render_template('result.html', result=result)
#     """
#     if 'fileToUpload' not in request.files:
#         return 'No file uploaded.'

#     file = request.files['fileToUpload']
#     img = image.load_img(file, target_size=(224, 224))
#     img_array = image.img_to_array(img)
#     img_array = preprocess_input(img_array)
#     img_array = np.expand_dims(img_array, axis=0)

#     # Perform prediction using the loaded model
#     result = model.predict(img_array)
#     # Further processing and formatting of the result as needed

#     return render_template('result.html', result=result)

UPLOAD_FOLDER="E:/other/nm/myproject/upload"
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER

ALLOWED_EXTENSIONS = {'txt', 'pdf', 'png', 'jpg', 'jpeg', 'gif'}

def allowed_file(filename):
    return '.' in filename and filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

model = load_model('E:\other\\nm\\vgg-16-Tea-leaves-disease-model.h5')
class_labels = {0: 'Anthracnose',1: 'algal leaf',2: 'bird eye spot', 3: 'brown blight',4: 'gray light',5: 'healthy',6: 'red leaf spot',7: 'white spot'}
@app.route('/process', methods=['GET', 'POST'])
def upload_file():
    if request.method == 'POST':
        if 'fileToUpload' not in request.files:
            return 'No file uploaded.'

        file = request.files['fileToUpload']
        filename = secure_filename(file.filename)
        image_path = os.path.join(app.config['UPLOAD_FOLDER'], filename)
        file.save(image_path)
        img = image.load_img(image_path, target_size=(224, 224))
        img = image.img_to_array(img)
        img = preprocess_input(img.reshape((1, img.shape[0], img.shape[1], img.shape[2])))
        predictions = model.predict(img)
        predicted_class = predictions.argmax()
        predicted_label = class_labels.get(predicted_class, 'Unknown')
        return render_template('result.html', result=predicted_label)
    return render_template('prediction.html')

@app.route('/result')
def result():
    return render_template('result.html')

if __name__ == '__main__':
    #app = Flask(__name__, template_folder='E:\\other\\nm\\myproject\\templates')
    app.run(debug=True,port=5000)
