# HomeSensorsSimulator
This C++ program simulates **real-time** home sensor data for older adults. This is Part I of a data engineering pipeline showcase, from a healthcare context.

## The problem
There is a push towards **Ageing in Place (AIP)** and older adults maintaining independence by living in their own homes for as long as possible. This is made possible with support from informal carers (e.g. family), formal carers (e.g. personal social services) and technology (e.g. **Smart Home/Internet of Things (IoT)**). It has been well established that older adults generally prefer *not* to have privacy invading technology in their homes. However, passive infrared (PIR) sensors have been shown to be acceptable as they are associated with home security. 

## The solution
Monitoring movement around the home (e.g. using PIR sensors) is one of many possible approaches towards adding an additional layer of safety for AIP. This may be used in the context of vulnerability towards falls, detecting deterioration in **activities of daily living** (and therefore the need for additional support) or the onset of intercurrent illness (e.g. pneumonia).

## The technology
In the context of a lack of real world data, it can be useful to simulate *real-time* sensor data to develop approaches towards effective monitoring of home activity. Home activity data should ideally be used in the context of other data, for example baseline data from an older adult's eletronic medical record (e.g. underlying medical problems), wearable device data (e.g. physiological parameters) or direct questioning. However, there can be issues with the uptake and ongoing use of wearables (e.g. smart watches). Direct questioning is perhaps the weakest data source because there may be a delay in recognition of a problem from the older adult's perspective. The aim of this program is to simulate *real-time* home sensor data (e.g. PIR, pressure sensor, door sensor etc.). 

### Why C++?
This program is written in C++, but could have equally have been written in Python or really any other language. C++ was chosen due to the fact this can be easily compiled and run on any device/platform. Whilst obviously this could be run on a cloud server, this would suit being run in real-time on a Rasberry Pi as it is low cost and can be left to run night and day. The idea was to stay true to the embedded software underlying the sensor data (e.g. a home hub collecting sensor data and pushing to a server in real-time). Furthermore, if there was a need to really expand this and generate millions of simulated agents/sensors, C++ will scale nicely. This is an iterative project and more complexity, testing etc. will be added soon.

### What sensors can we simulate?

- PIR sensors (for movement between rooms)
- Pressure sensors (e.g. bed and chair)
- Door sensors (e.g. front/back door, fridge etc)

### Simulating older adults
This is a essentially a form of **agent-based modelling**. Older adults (the 'agents') tend to follow a routine, having established this for many years. Whilst we want to account for individual daily variation we want to simulate a range of wake-up and bed times across the agents with fairly consistent individual (intra-agent) variation, but signficiant population (inter-agent) variation. Once a routine is established, for some agents we want to randomly deviate from this in particular ways that have been demonstrated to relate to problems in previous research. The three main patterns we want to simulate are as follows: -

1. Wake-up sensor triggered, but then no further activity for > 45 minutes. This can signify a fall trying to get out of bed. 
2. Spending more time than usual in a chair or bed. This can occur in intercurrent illness (e.g. infection).
3. Using the toilet at night time. This can commonly occur in men due to benign prostatic hyperplasia, but can also represent a new urinary tract infection in either gender.

### Data pipeline
In reality this program would be simulating a home hub, consumer Smart Home device or mobile application sending sensor data to a remote server in real-time, probably in individual batches at a preset timeframe (e.g. 10 minutes). Data would converge onto a server, possibly a dedicated IoT gateway or REST API for initial processing, and then transfered to a database (e.g. SQL) for persistence. In *Part II* of this data engineering showcase a dedicated REST API built using Scala will be setup to handle this data.

### Data analysis
The nature of this data is a prime example of a use case for unsupervised machine learning, in this case anomaly detection. The system would learn the normal intra-agent variation and highlight anomalies. It should be sensitive enough to pick out the three main patterns we want to detect as describe earlier, but specific enough to ignore normal intra-agent variation. In *Part III* of this showcase, an anomaly detection system will be setup and deployed into 'production', to analyse data from the pipeline.

### Other considerations
In further parts of this showcase, other aspects of data engineering will be covered, including Extract Transform Load (ETL) and Extract Load Transform (ELT) using modern tools (e.g. Stitch, Fivetran etc.) to move and process legacy data to a data warehouse/lake. We will also look at analytics using popular tools (e.g. Looker, Tableau etc.) 
