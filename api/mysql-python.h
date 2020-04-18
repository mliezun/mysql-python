extern "C" bool py_eval_init(UDF_INIT *initid, UDF_ARGS *args,
                             char *message);
extern "C" char *py_eval(UDF_INIT *, UDF_ARGS *args, char *result,
                         unsigned long *res_length, unsigned char *null_value,
                         unsigned char *);