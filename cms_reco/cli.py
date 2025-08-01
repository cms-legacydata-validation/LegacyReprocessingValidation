#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# This file is part of reana.
# Copyright (C) 2019 CERN.
#
# REANA is free software; you can redistribute it and/or modify it
# under the terms of the MIT License; see LICENSE file for more details.

"""Reana workflow factory cli."""

import logging
import os
import sys

import click
from cookiecutter.exceptions import OutputDirExistsException
from cookiecutter.main import cookiecutter
from .utils import (get_config_from_json, get_template, load_config_from_cod,
                    valid_compute_backends, valid_file_selection,
                    valid_run_years, valid_workflow_engines)


@click.group()
def cms_reco():
    """Workflow factory for the cms reconstruction analysis."""
    pass


@click.option('--config_file',
              default='cms_reco/cms-reco-config.json',
              help='recid for the data set to be reconstructed')
@click.option('--recid',
              help='recid for the data set to be reconstructed')
@cms_reco.command()
def load_config(recid, config_file):
    """Download config file using the cern-open-data client."""
    load_config_from_cod(recid, config_file)
    print("Downloaded config file from cod as {}.".format(config_file))


@click.option('--config_file',
              default="cms_reco/cms-reco-config.json",
              help='the config file used to extract the parameters')
@click.option('--compute_backend',
              default='kubernetes',
              help='compute backend to be used',
              type=click.Choice(valid_compute_backends))
@click.option('--dataset',
              default="DoubleElectron",
              help='data set to be reconstructed')
@click.option('--directory',
              default='',
              help='directory for the analysis to be executed')
@click.option('--files',
              default='first',
              help='choose a specific file from the index',
              type=click.Choice(valid_file_selection))
@click.option('--nevents',
              default='1',  # ToDo: change to "-1" for full data set reco
              help='number of events to be reconstructed')
@click.option('--quiet', is_flag=True,
              help='No diagnostic output')
@click.option('--workflow_engine',
              default='serial',
              help='workflow engine to be used',
              type=click.Choice(valid_workflow_engines))
@click.option('--year',
              default="2011",
              help='year the data set was recorded',
              type=click.Choice(valid_run_years))
@click.option('--recid',
              default=None,
              help='CMS Open Data record ID for dataset configuration')
@cms_reco.command()
def create_workflow(config_file, compute_backend, dataset, directory, files,
                    nevents, quiet, workflow_engine, year, recid):
    """Create workflow from json config file or from given arguments."""
    logging.basicConfig(
        format='[%(levelname)s] %(message)s',
        stream=sys.stderr,
        level=logging.INFO if quiet else logging.DEBUG)
        
    # If recid provided, download config first
    if recid:
        load_config_from_cod(recid, config_file)
        logging.info(f"Downloaded config file from COD record {recid}")
    
    # Set COD configs
    config = get_config_from_json(config_file=config_file, file_selection=files)

    if config['error']:
        logging.warning(config['error'])
    else:

        # Set REANA (non-COD) related configs
        config['compute_backend'] = compute_backend
        # Always add recid from CLI parameter (overrides any from JSON)
        config['recid'] = str(recid) if recid else None

        # Set optional configs
        if nevents:
            config['nevents'] = nevents
        if directory:
            config['directory_name'] = directory

        try:
            cookiecutter(get_template(workflow_engine),
                         no_input=True,
                         extra_context=config)
        except OutputDirExistsException:
            logging.warning("Output Directory already exists, please choose a "
                            "different name or rename the existing one.")
        print("Created `{0}` directory.".format(config["directory_name"]))
