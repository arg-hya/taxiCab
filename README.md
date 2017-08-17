# **taxiCab**
Analysis of taxicab trajectories in NY region.

#**DataCleanUP**

1.> *Run the exe*
Cleans the data.
Put the Jan data in Data\1\
The cleand up data will be generated in Output\

2.> *Run the python scripts present in Output\*
Converts Lat, Lon to projected co-ordinates

#**TrajectoryFormation**

**1.>	Put the cleanup data into TrajectoryFormation\Data**

##GenerateSampledID

**1.> Run the exe**
Generates 5000 unique sampled cab IDs
Output file : "sampled.txt" in Data\1\

##TrajectoryFormation

**1.> Run the exe**
Creates 5000 trajectory files
Output : "{cabID}_trajectory.traj" in Output\

##Discritization

**1.> Run the exe**
Creates 5000 sampled trajectory files of 720 length each
Output : "{cabID}_sampled.traj" in Output\

##Optimization

1.> Put "TestTask.data" in Output\
2.> Run the exe
The optimizing algorithm 
Output : "FinalClusters.data" in Output\
Contains the clustered cab IDs along with their cluster prototype

##TaskAssingAndEvaluation

1.> Put "SpecifiedTasks.data" in Output\
2.> Run the exe
Assigns Tasks specified in "SpecifiedTasks.data" to suitable cluster
Output: "ClusterID_TaskAssignation.data" in Output\
	contains Cluster ID of each corresponding task




