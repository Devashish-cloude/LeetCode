
int earliestFinishTime(int* landStartTime, int landStartTimeSize,
                       int* landDuration, int landDurationSize,
                       int* waterStartTime, int waterStartTimeSize,
                       int* waterDuration, int waterDurationSize) {
    int ans = 1000000000;

    // Land ride first, then water ride
    for (int i = 0; i < landStartTimeSize; i++) {
        int landFinish = landStartTime[i] + landDuration[i];

        for (int j = 0; j < waterStartTimeSize; j++) {
            int start = landFinish > waterStartTime[j]
                        ? landFinish : waterStartTime[j];

            int finish = start + waterDuration[j];

            if (finish < ans)
                ans = finish;
        }
    }

    // Water ride first, then land ride
    for (int i = 0; i < waterStartTimeSize; i++) {
        int waterFinish = waterStartTime[i] + waterDuration[i];

        for (int j = 0; j < landStartTimeSize; j++) {
            int start = waterFinish > landStartTime[j]
                        ? waterFinish : landStartTime[j];

            int finish = start + landDuration[j];

            if (finish < ans)
                ans = finish;
        }
    }

    return ans;
}
