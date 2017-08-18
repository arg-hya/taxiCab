# **taxiCab**
Analysis of taxicab trajectories in NY region.

Run the modules in order as listed below :

# **DataCleanUP**

**1.> Run the exe**

Cleans the data.
Put the Jan data in Data\1\
The cleand up data will be generated in Output\

**2.>  Run the python scripts present in Output **

Converts Lat, Lon to projected co-ordinates

# **TrajectoryFormation**

**1.>	Put the cleanup data into TrajectoryFormation\Data**

GenerateSampledID
-----------------

**1.> Run the exe**

Generates 5000 unique sampled cab IDs
Output file : "sampled.txt" in Data\1\

TrajectoryFormation
-------------------

**1.> Run the exe**

Creates 5000 trajectory files
Output : "{cabID}_trajectory.traj" in Output\

Discritization
-----------------

**1.> Run the exe**

Creates 5000 sampled trajectory files of 720 length each
Output : "{cabID}_sampled.traj" in Output\

# **TraNodeCreator**

Generate Node Points
--------------------

**1.> Run NodePointGenerator.py**

Generates 263 node points corresponding to each taxi zone
Output file : "NodePoints.data" 

TrajectoryFormation
-------------------

**1.> Run TrajToNodeConverter.py**

Converts the sampled trajectories generated to node point representation
Output : "AllTrajecsNopePoints.data" 

# **TrajectoryFormation**

TrajSplit
----------

**1.> Run the exe**

Trajectory splitting is performed
Output file : "{cabID}_{Split_number}.traj" in Output\Split

# **Clustering**

**1.> Copy "Split" folder to "Clustering\Parallel\" **
**2.> Copy "Sampled.txt" folder to "Clustering\Parallel\" ****

Clustering\Parallel\Split_Clustering
------------------------------------

**1.> Run ClusterGenerator.py**
Output file : "FinalClusters_before_Optimization.csv"

# **TrajectoryFormation**

**1.> Copy "FinalClusters_before_Optimization.csv" folder to "Output\" **
**2.> Copy "TestTask.data" folder to "Output\" ****

Optimization
------------

**1.> Put "TestTask.data" in Output **
**2.> Run the exe**

The optimizing algorithm 
Output : "FinalClusters.data" in Output\
Contains the clustered cab IDs along with their cluster prototype

**1.> Copy "SpecifiedTasks.data" folder to "Output\" **

TaskAssingAndEvaluation
-----------------------

**1.> Put "SpecifiedTasks.data" in Output **
**2.> Run the exe**

Assigns Tasks specified in "SpecifiedTasks.data" to suitable cluster
Output: "ClusterID_TaskAssignation.data" in Output\
	contains Cluster ID of each corresponding task




