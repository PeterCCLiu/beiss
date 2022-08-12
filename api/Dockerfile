#sudo apt-get install libgmp3-dev
#wget https://crypto.stanford.edu/pbc/files/pbc-0.5.14.tar.gz
#unzip pbc-0.5.14.tar.gz
#cd pbc-0.5.14
#./configure
#make
#make install
# sudo apt-get install ninja-build

FROM node:18

WORKDIR /usr/src/app

COPY package*.json ./

RUN npm install

COPY . .

EXPOSE 3000

CMD npm run devStart