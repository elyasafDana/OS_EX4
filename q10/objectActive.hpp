// objectActive.hpp (רק הצהרות)
class MaxCliqueStage; class MstStage; class MaxFlowStage;
class EulerStage {
public:
    void start();
    void post(ReqPtr r);
    void stop();
    void set_next(MaxFlowStage* n);
private:
    void run();            // רק הצהרה
    MaxFlowStage* next;
    TSQueue<ReqPtr> q;
    std::thread th;
    std::atomic<bool> started{false};
};

class MaxFlowStage {
public:
    void start();
    void post(ReqPtr r);
    void stop();
    void set_next(MaxCliqueStage* n);
private:
    void run();            // רק הצהרה
    MaxCliqueStage* next;  // מותר; מצביע למחלקה קדימה-מוצהרת
    TSQueue<ReqPtr> q;
    std::thread th;
    std::atomic<bool> started{false};
};

class MaxCliqueStage {
public:
    void start();
    void post(ReqPtr r);
    void stop();
    void set_next(MstStage* n);
private:
    void run();            // רק הצהרה
    MstStage* next;
    TSQueue<ReqPtr> q;
    std::thread th;
    std::atomic<bool> started{false};
};

class MstStage {
public:
    void start();
    void post(ReqPtr r);
    void stop();
private:
    void run();            // רק הצהרה
    TSQueue<ReqPtr> q;
    std::thread th;
    std::atomic<bool> started{false};
};
