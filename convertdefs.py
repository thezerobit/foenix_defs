import os, re

NUMBER_RE = re.compile("^\d+$")

ADDR_RE = re.compile("^\$\d{6}$")

UNKNOWN = object()
BLANK = object()
COMMENT = object()
DEFINITION = object()

def to_c(value, var_name):
	if value.startswith("$"):
		value = "0x{}".format(value.strip("$"))
	return value

def format_comment(comment):
	clean = comment.replace("*/","")
	return "/* {} */".format(clean)

def write_group(group, group_type, f):
	if group_type == UNKNOWN:
		for line in group:
			f.write("/* UNHANDLED FORM: {}*/\n".format(line))
	elif group_type == BLANK:
		for _ in group:
			f.write("\n")
	elif group_type == COMMENT:
		for comment in group:
			f.write(format_comment(comment) + "\n")
	elif group_type == DEFINITION:
		max_var_length = 0
		max_val_length = 0
		for var_name, value, comment in group:
			if len(var_name) > max_var_length:
				max_var_length = len(var_name)
			if len(value) > max_val_length:
				max_val_length = len(value)
		for var_name, value, comment in group:
			value = to_c(value, var_name)
			if len(var_name) < max_var_length:
				var_name = var_name + (" " * (max_var_length - len(var_name)))
			if len(value) < max_val_length:
				value = value + (" " * (max_val_length - len(value)))
			if comment == "":
				f.write("#define {} {}\n".format(var_name, value, comment))
			else:
				f.write("#define {} {} {}\n".format(var_name, value, format_comment(comment)))

def convert_files():
	path_to_defs = os.path.normpath("../Kernel_FMX/src/Defines")

	defs = [x for x in os.listdir(path_to_defs) if x.endswith("_def.asm")]

	for name in defs:
		file_path = os.path.join(path_to_defs, name)
		print("processing: " + file_path)
		with open(file_path, "r") as f:
			lines = f.readlines()
		name_prefix = name.split(".asm")[0]
		header_file = name_prefix + ".h"
		header_path = os.path.join("defs", header_file)
		print("writing: " + header_path)
		with open(header_path, "w") as f:
			define_name = header_file.replace(".", "_").upper()
			f.write("#ifndef {}\n".format(define_name))
			f.write("#define {}\n".format(define_name))
			group = []
			group_type = UNKNOWN
			for line in lines:
				type_ = UNKNOWN

				parts = line.split(";", 1)
				comment = parts[1].strip() if len(parts) > 1 else ""
				code_parts = parts[0].split()
				var_name = ""
				value = ""
				if len(code_parts) == 3 and code_parts[1] == "=":
					var_name = code_parts[0]
					value = code_parts[2]
					type_ = DEFINITION

				if var_name == "" and comment == "":
					type_ = BLANK
				elif var_name == "" and comment != "":
					type_ = COMMENT

				if group_type != type_:
					write_group(group, group_type, f)
					group = []
					group_type = type_

				if type_ == UNKNOWN:
					group.append((line.strip()))
				elif group_type == BLANK:
					group.append(())
				elif group_type == COMMENT:
					group.append(comment)
				elif group_type == DEFINITION:
					group.append((var_name, value, comment))

				group_type = type_
			if len(group) > 0:
				write_group(group, group_type, f)
			f.write("#endif\n")

if __name__ == "__main__":
	convert_files()