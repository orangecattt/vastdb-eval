#include <stdint.h>
#include <stddef.h>
#include <errno.h>

#define AV_LOG_ERROR 16

#define AVERROR(code) (-(code))

#define ENOMEM 12
#define EINVAL 22

typedef struct AVFrame AVFrame;
typedef struct AVClass AVClass;
typedef struct Queue Queue;
typedef struct SafeQueue SafeQueue;
typedef struct AVFilterContext AVFilterContext;

#define DNN_GENERIC_ERROR FFERRTAG('D','N','N','!')

typedef enum {
    DNN_TF = 1,
    DNN_OV = 1 << 1,
    DNN_TH = 1 << 2
} DNNBackendType;

typedef enum {
    DCO_NONE,
    DCO_BGR,
    DCO_RGB,
} DNNColorOrder;

typedef enum {
    DFT_NONE,
    DFT_PROCESS_FRAME,
    DFT_ANALYTICS_DETECT,
    DFT_ANALYTICS_CLASSIFY,
} DNNFunctionType;

typedef enum {
    DL_NONE,
    DL_NCHW,
    DL_NHWC,
} DNNLayout;

typedef enum {
    DNN_FLOAT = 1,
    DNN_UINT8 = 4
} DNNDataType;

typedef struct DNNData {
    void *data;
    int dims[4];
    DNNDataType dt;
    DNNColorOrder order;
    DNNLayout layout;
    float scale;
    float mean;
} DNNData;

typedef int (*FramePrePostProc)(AVFrame *frame, DNNData *model, AVFilterContext *filter_ctx);
typedef int (*DetectPostProc)(AVFrame *frame, DNNData *output, uint32_t nb, AVFilterContext *filter_ctx);
typedef int (*ClassifyPostProc)(AVFrame *frame, DNNData *output, uint32_t bbox_index, AVFilterContext *filter_ctx);

typedef struct DNNExecBaseParams {
    const char *input_name;
    const char **output_names;
    uint32_t nb_output;
    AVFrame *in_frame;
    AVFrame *out_frame;
} DNNExecBaseParams;

typedef struct DNNModel {
    AVFilterContext *filter_ctx;
    DNNFunctionType func_type;
    int (*get_input)(struct DNNModel *model, DNNData *input, const char *input_name);
    int (*get_output)(struct DNNModel *model, const char *input_name, int input_width, int input_height,
                                const char *output_name, int *output_width, int *output_height);
    FramePrePostProc frame_pre_proc;
    FramePrePostProc frame_post_proc;
    DetectPostProc detect_post_proc;
    ClassifyPostProc classify_post_proc;
} DNNModel;

typedef struct TFOptions {
    const AVClass *clazz;
    char *sess_config;
} TFOptions;

typedef struct DNNModule DNNModule;

typedef struct DnnContext {
    const AVClass *clazz;
    DNNModel *model;
    char *model_filename;
    DNNBackendType backend_type;
    char *model_inputname;
    char *model_outputnames_string;
    char *backend_options;
    int async;
    char **model_outputnames;
    uint32_t nb_outputs;
    const DNNModule *dnn_module;
    int nireq;
    char *device;
#if CONFIG_LIBTENSORFLOW
    TFOptions tf_option;
#endif
#if CONFIG_LIBOPENVINO
    OVOptions ov_option;
#endif
#if CONFIG_LIBTORCH
    THOptions torch_option;
#endif
} DnnContext;

typedef struct TaskItem {
    void *model;
    AVFrame *in_frame;
    AVFrame *out_frame;
    const char *input_name;
    const char **output_names;
    uint8_t async;
    uint8_t do_ioproc;
    uint32_t nb_output;
    uint32_t inference_todo;
    uint32_t inference_done;
} TaskItem;

typedef struct LastLevelTaskItem {
    TaskItem *task;
    uint32_t bbox_index;
} LastLevelTaskItem;

typedef enum {
    DAST_FAIL,
    DAST_EMPTY_QUEUE,
    DAST_NOT_READY,
    DAST_SUCCESS
} DNNAsyncStatusType;

typedef struct DNNAsyncExecModule {
    int (*start_inference)(void *request);
    void (*callback)(void *args);
    void *args;
#if HAVE_PTHREAD_CANCEL
    pthread_t thread_id;
    pthread_attr_t thread_attr;
#endif
} DNNAsyncExecModule;

typedef struct TF_Graph TF_Graph;
typedef struct TF_Session TF_Session;
typedef struct TF_Status TF_Status;

typedef struct TFModel {
    DNNModel model;
    DnnContext *ctx;
    TF_Graph *graph;
    TF_Session *session;
    TF_Status *status;
    SafeQueue *request_queue;
    Queue *lltask_queue;
    Queue *task_queue;
} TFModel;

typedef struct TF_Output {
    struct TF_Operation *oper;
    int index;
} TF_Output;

typedef struct TF_Tensor TF_Tensor;

typedef struct TFInferRequest {
    TF_Output *tf_outputs;
    TF_Tensor **output_tensors;
    TF_Output *tf_input;
    TF_Tensor *input_tensor;
} TFInferRequest;

typedef struct TFRequestItem {
    TFInferRequest *infer_request;
    LastLevelTaskItem *lltask;
    TF_Status *status;
    DNNAsyncExecModule exec_module;
} TFRequestItem;

Queue *ff_queue_create(void);
void ff_queue_destroy(Queue *q);
size_t ff_queue_size(Queue *q);
void *ff_queue_peek_front(Queue *q);
void *ff_queue_peek_back(Queue *q);
int ff_queue_push_front(Queue *q, void *v);
int ff_queue_push_back(Queue *q, void *v);
void *ff_queue_pop_front(Queue *q);
void *ff_queue_pop_back(Queue *q);

SafeQueue *ff_safe_queue_create(void);
void ff_safe_queue_destroy(SafeQueue *sq);
size_t ff_safe_queue_size(SafeQueue *sq);
int ff_safe_queue_push_front(SafeQueue *sq, void *v);
int ff_safe_queue_push_back(SafeQueue *sq, void *v);
void *ff_safe_queue_pop_front(SafeQueue *sq);

int ff_check_exec_params(void *ctx, DNNBackendType backend, DNNFunctionType func_type, DNNExecBaseParams *exec_params);
int ff_dnn_fill_task(TaskItem *task, DNNExecBaseParams *exec_params, void *backend_model, int async, int do_ioproc);
int ff_dnn_async_module_cleanup(DNNAsyncExecModule *async_module);
int ff_dnn_start_inference_async(void *ctx, DNNAsyncExecModule *async_module);
DNNAsyncStatusType ff_dnn_get_result_common(Queue *task_queue, AVFrame **in, AVFrame **out);
int ff_dnn_fill_gettingoutput_task(TaskItem *task, DNNExecBaseParams *exec_params, void *backend_model, int input_height, int input_width, void *ctx);

void *av_malloc(size_t size) ;
void av_freep(void *arg);
void av_log(void *avcl, int level, const char *fmt, ...);

static int execute_model_tf(TFRequestItem *request, Queue *lltask_queue);

static int extract_lltask_from_task(TaskItem *task, Queue *lltask_queue)
{
    TFModel *tf_model = task->model;
    DnnContext *ctx = tf_model->ctx;
    LastLevelTaskItem *lltask = av_malloc(sizeof(*lltask));
    if (!lltask) {
        av_log(ctx, AV_LOG_ERROR, "Unable to allocate space for LastLevelTaskItem\n");
        return AVERROR(ENOMEM);
    }
    task->inference_todo = 1;
    task->inference_done = 0;
    lltask->task = task;
    if (ff_queue_push_back(lltask_queue, lltask) < 0) {
        av_log(ctx, AV_LOG_ERROR, "Failed to push back lltask_queue.\n");
        av_freep(&lltask);
        return AVERROR(ENOMEM);
    }
    return 0;
}

static int dnn_execute_model_tf(const DNNModel *model, DNNExecBaseParams *exec_params)
{
    TFModel *tf_model = (TFModel *)model;
    DnnContext *ctx = tf_model->ctx;
    TaskItem *task;
    TFRequestItem *request;
    int ret = 0;

    ret = ff_check_exec_params(ctx, DNN_TF, model->func_type, exec_params);
    if (ret != 0) {
        return ret;
    }

    task = av_malloc(sizeof(*task));
    if (!task) {
        av_log(ctx, AV_LOG_ERROR, "unable to alloc memory for task item.\n");
        return AVERROR(ENOMEM);
    }

    ret = ff_dnn_fill_task(task, exec_params, tf_model, ctx->async, 1);
    if (ret != 0) {
        av_log(ctx, AV_LOG_ERROR, "Fill task with invalid parameter(s).\n");
        av_freep(&task);
        return ret;
    }

    if (ff_queue_push_back(tf_model->task_queue, task) < 0) {
        av_freep(&task);
        av_log(ctx, AV_LOG_ERROR, "unable to push back task_queue.\n");
        return AVERROR(ENOMEM);
    }

    ret = extract_lltask_from_task(task, tf_model->lltask_queue);
    if (ret != 0) {
        av_freep(&task);
        av_log(ctx, AV_LOG_ERROR, "unable to extract last level task from task.\n");
        return ret;
    }

    request = ff_safe_queue_pop_front(tf_model->request_queue);
    if (!request) {
        av_freep(&task);
        av_log(ctx, AV_LOG_ERROR, "unable to get infer request.\n");
        return AVERROR(EINVAL);
    }
    return execute_model_tf(request, tf_model->lltask_queue);
}
