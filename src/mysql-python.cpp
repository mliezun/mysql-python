#include <pybind11/embed.h>
#include <pybind11/eval.h>
#include <string.h>
#include "udf_registration_types.h"

namespace py = pybind11;

py::scoped_interpreter guard{};

/***************************************************************************
** UDF py_eval function.
** Arguments:
** initid	Structure filled by xxx_init
** args		The same structure as to xxx_init. This structure
**		contains values for all parameters.
**		Note that the functions MUST check and convert all
**		to the type it wants!  Null values are represented by
**		a NULL pointer
** is_null	If the result is null, one should store 1 here.
** error	If something goes fatally wrong one should store 1 here.
**
** This function should return the result.
***************************************************************************/

extern "C" bool py_eval_init(UDF_INIT *initid, UDF_ARGS *args,
                             char *message)
{
    if (args->arg_count != 1)
    {
        strcpy(message, "py_eval must have one argument");
        return true;
    }
    args->arg_type[0] = STRING_RESULT;
    initid->maybe_null = true; /* The result may be null */
    return false;
}

extern "C" char *py_eval(UDF_INIT *, UDF_ARGS *args, char *result,
                         unsigned long *res_length, unsigned char *null_value,
                         unsigned char *)
{
    auto obj = py::eval(args->args[0]);
    std::string res_str = std::string(py::str(obj));

    strcpy(result, res_str.c_str());

    *res_length = res_str.length();

    return result;
}
